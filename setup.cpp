#include "setup.h"
#include "PythonRunner.h"
#include <filesystem>
#include <cstdlib>

void run_first_time_setup()
{
    if(std::filesystem::exists("setup.flag")) return ;
    run_cmd_and_wait("setup.bat");
    // run_cmd_and_wait("python\\python.exe python\\get-pip.py ^ python\\python.exe -m pip install -r requirements.txt ^ python\\python.exe -m playwright install chromium ^ echo setup_complete > setup.flag");
    // run_cmd_and_wait("python\\python.exe -m pip install -r requirements.txt");
    // run_cmd_and_wait("python\\python.exe -m playwright install chromium");
    // run_cmd_and_wait("echo setup_complete > setup.flag");
    
}