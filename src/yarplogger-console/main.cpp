/* 
 * Copyright (C)2014  iCub Facility - Istituto Italiano di Tecnologia
 * Author: Marco Randazzo
 * email:  marco.randazzo@iit.it
 * website: www.robotcub.org
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include <yarp/os/Network.h>
#include <yarp/os/Port.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Time.h>
#include <yarp/os/Vocab.h>
#include <yarp/os/RFModule.h>
#include <yarp/logger/YarpLogger.h>

#include <string>
#include <stdio.h>

using namespace yarp::os;
using namespace yarp::yarpLogger;

class logger_module : public yarp::os::RFModule
{
    LoggerEngine* the_logger;

    protected:
    yarp::os::Port rpcPort;

    virtual bool configure(yarp::os::ResourceFinder &rf)
    {
        the_logger = new LoggerEngine ("/logger");

        rpcPort.open("/logger/rpc:i");
        attach(rpcPort);
        //attachTerminal();

        the_logger->start_logging();
        return true;
    }

    virtual bool interruptModule()
    {
        rpcPort.interrupt();
        return true;
    }

    virtual bool close()
    {
        rpcPort.interrupt();
        rpcPort.close();

        if (the_logger)
        {
            delete the_logger;
            the_logger=NULL;
        }
        return true;
    }

    virtual double getPeriod()
    {
        return 10.0; 
    }
    
    virtual bool updateModule()
    {
        printf("logger running, listening to %d ports\n",the_logger->get_num_of_processes());
        return true; 
    }

    virtual bool respond(const yarp::os::Bottle& command,yarp::os::Bottle& reply) 
    {
        reply.clear();
        if (command.get(0).asString()=="quit")
        {
            reply.addString("ack");
            return false;
        }
        else if (command.get(0).asString()=="start")
        {
            if (the_logger->is_logging()==false)
            {
                this->the_logger->start_logging();
            }
            reply.addString("ack");
        }
        else if (command.get(0).asString()=="stop")
        {
            if (the_logger->is_logging()==true)
            {
                this->the_logger->stop_logging();
            }
            reply.addString("ack");
        }
        else if (command.get(0).asString()=="save")
        {
            std::string filename = command.get(1).asString();
            this->the_logger->save_all_logs_to_file(filename);
            reply.addString("ack");
        }
        else if (command.get(0).asString()=="load")
        {
            std::string filename = command.get(1).asString();
            this->the_logger->load_all_logs_from_file(filename);
            reply.addString("ack");
        }
        else if (command.get(0).asString()=="ask_by_proc")
        {
            std::string proc_name = command.get(1).asString();
            std::list<MessageEntry> m;
            the_logger->get_messages_by_process(proc_name, m);
            std::list<MessageEntry>::iterator it;
            for (it = m.begin(); it != m.end(); it++)
                printf(" %s %d %s \n",it->yarprun_timestamp.c_str(), it->level.toInt(), it->text.c_str());
            reply.addString("ack");
        }
        else if (command.get(0).asString()=="ask_all")
        {
             std::list<MessageEntry> m;
             the_logger->get_messages(m);
             std::list<MessageEntry>::iterator it;
             for (it = m.begin(); it != m.end(); it++)
                 printf(" %s %d %s \n",it->yarprun_timestamp.c_str(), it->level.toInt(), it->text.c_str());
             reply.addString("ack");
        }
        else if (command.get(0).asString()=="discover")
        {
             std::list<std::string> ports;
             the_logger->discover(ports);
             reply.addString("ack");
        }
        else if (command.get(0).asString()=="connect")
        {
             std::list<std::string> ports;
             the_logger->discover(ports);
             the_logger->connect(ports);
             reply.addString("ack");
        }
        else if (command.get(0).asString()=="get_info")
        {
             std::list<LogEntryInfo> infos;
             the_logger->get_infos(infos);
             std::list<LogEntryInfo>::iterator it;
             for (it = infos.begin(); it != infos.end(); it++)
             {
                 std::tm* tm = localtime(&it->last_update);
                 if (tm)
                 printf("%s %s hour:%d minute:%d sec:%d \n",it->port_prefix.c_str(), it->port_complete.c_str(), tm->tm_hour,tm->tm_min, tm->tm_sec);
                 else
                 printf("%s %s no data received yet \n",it->port_prefix.c_str(), it->port_complete.c_str());
             }
             reply.addString("ack");
        }
        else
        {
            reply.addString("nack");
        }
        return true;
    }
};

int main(int argc, char *argv[]) 
{
    yarp::os::Network yarp;
    if (!yarp.checkNetwork())
    {
        fprintf(stderr,"ERROR: check Yarp network.\n");
        return -1;
    }

    yarp::os::ResourceFinder rf;
    rf.setVerbose(true);
    rf.setDefaultConfigFile("yarprunLogger.ini");           //overridden by --from parameter
    rf.setDefaultContext("yarprunLogger");                  //overridden by --context parameter
    rf.configure(argc,argv);

    logger_module icub_logger;
    return icub_logger.runModule(rf);
}
