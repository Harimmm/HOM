#include "Network/server/dbus.h"

namespace Test{
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus_message *m = NULL;
    sd_bus *bus = NULL;

    const char *sig;
    int ret; //에러 발생 확인용. ret 음수일 경우 에러 발생한 것

    const char *msg; //일반적인 메세지 read
    int num; //int 형식의 메세지를 read
    const char* name;
    const char* seat;
    const char* op;

    void service(const std::string& text){
        ret = sd_bus_default_system(&bus);

        //std::cout<<"Connected!"<<std::endl;

        /*Create User*/
        if(text=="CreateUser\n"){
            ret = sd_bus_call_method(bus,"org.freedesktop.Accounts",
                "/org/freedesktop/Accounts",
                "org.freedesktop.Accounts",
                "CreateUser",
                &error,
                &m,"ssi","testname", "testname", 0);
        }
        /*Lock Session*/
        else if(text=="LockSession\n"){
            ret = sd_bus_call_method(bus,"org.freedesktop.login1",
                "/org/freedesktop/login1/session/self",
                "org.freedesktop.login1.Session",
                "Lock",
                &error,
                &m,"","");
        }
        /*Power Off*/
        else if(text=="PowerOff\n"){
            ret = sd_bus_call_method(bus,"org.freedesktop.login1",
                "/org/freedesktop/login1",
                "org.freedesktop.login1.Manager",
                "PowerOff",
                &error,
                &m,"b","true");
        }
        /*Reboot*/
        else if(text=="Reboot\n"){
            ret = sd_bus_call_method(bus,"org.freedesktop.login1",
                "/org/freedesktop/login1",
                "org.freedesktop.login1.Manager",
                "Reboot",
                &error,
                &m,"b","true");
        }
        /*List Sessions*/
        else if(text=="ListSessions\n"){
            ret = sd_bus_call_method(bus,"org.freedesktop.login1",
                "/org/freedesktop/login1",
                "org.freedesktop.login1.Manager",
                "ListSessions",
                &error,
                &m,"","");
            
            ret = sd_bus_message_enter_container(m, 'a', "(susso)");
            while((ret = sd_bus_message_read(m, "(susso)", &msg, &num, &name, &seat, &op))>0){
                std::cout<<msg<<std::endl;
                std::cout<<num<<std::endl;
                std::cout<<name<<std::endl;
                std::cout<<seat<<std::endl;
                std::cout<<op<<std::endl;
            };
            ret = sd_bus_message_exit_container(m);
        }
        /*List Users*/
        else if(text=="ListUsers\n"){
            ret = sd_bus_call_method(bus,"org.freedesktop.login1",
                "/org/freedesktop/login1",
                "org.freedesktop.login1.Manager",
                "ListUsers",
                &error,
                &m,"","");
            
            ret = sd_bus_message_enter_container(m, 'a', "(uso)");
            while((ret = sd_bus_message_read(m, "(uso)", &num, &name, &op))>0){
                std::cout<<num<<std::endl;
                std::cout<<name<<std::endl;
                std::cout<<op<<std::endl;
            };
            ret = sd_bus_message_exit_container(m);
        }
        /*List Seats*/
        else if(text=="ListSeats\n"){
            ret = sd_bus_call_method(bus,"org.freedesktop.login1",
                "/org/freedesktop/login1",
                "org.freedesktop.login1.Manager",
                "ListSeats",
                &error,
                &m,"","");
            
            ret = sd_bus_message_enter_container(m, 'a', "(so)");
            while((ret = sd_bus_message_read(m, "(so)", &msg, &op))>0){
                std::cout<<msg<<std::endl;
                std::cout<<op<<std::endl;
            };
            ret = sd_bus_message_exit_container(m);
        }



    finish();
    }

    void finish(){
        sd_bus_error_free(&error);
        sd_bus_message_unref(m);
        sd_bus_unref(bus);
    }
};