#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<pthread.h>
#include <fstream>
#include<dirent.h>

using namespace std;

void list_proc()
{
    DIR *dir = opendir("/proc");
    struct dirent *entry;
    while((entry = readdir(dir))!=NULL)
    {
        if(isdigit(entry->d_name[0]))
        {
            string pid(entry->d_name);
            ifstream cmd("/proc" + pid + "/comm");
            string name;
            getline(cmd,name);
            cout<<"PID : "<<pid<<endl;

        }

    }
    closedir(dir);
    return;
}

void show_proc()
{
    string pid;
    cout<<"Enter Pid: ";
    cin>>pid;

    ifstream status("/proc/"+pid + "/status");
    string line;
    while(getline(status,line))
        cout<<line<<endl;
    return;
}

void kill_proc()
{
    int pid;
    cout<<"Enter PID to Kill : ";
    cin>>pid;
    if(kill(pid,SIGKILL) == 0)
        cout<<"Killed Process\n";
    else
        perror("kill");
    return;
}

void *monitor_thread(void*)
{
    while(true)
    {
        system("clear");
        system("ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -10");
        sleep(2);
    }
    return NULL;
}

void monitor()
{
    pthread_t tid;
    pthread_create(&tid,NULL, monitor_thread,NULL);
    cin.get(); cin.get();
    pthread_cancel(tid);
}

void top_mem()
{
    int fd[2];
    if(pipe(fd) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t pid = fork();
    if(pid == 0)
    {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("sh", "sh", "-c", "ps -eo pid,comm,%mem --sort=-%mem | head -10", NULL);
        perror("excelp failed");
        exit(1);
    }

    else if(pid>0)
    {
        close(fd[1]);
        char buffer[1024];
        ssize_t count;
        cout<<"\nTop Memory-Using Process:\n";
        while((count = read(fd[0], buffer, sizeof(buffer)-1)) > 0)
        {
            buffer[count] = '\0';
            cout << buffer;
        }
        wait(NULL);
    }

    else
        perror("fork failed");
}


//setting up the cli tool
int main()
{
    while(true)
    {
        cout<<"\n[1] List Processes\n[2] Show Process Details\n[3] Kill Process\n[4] Monitor Usage\n[5] Show Top Memory-Consuming Processes\n[6] Exit\nChoice : ";
        int ch;
        cin>>ch;
        switch(ch)
        {
            case 1: list_proc(); break;
            case 2: show_proc(); break;
            case 3: kill_proc(); break;
            case 4: monitor(); break;
            case 5: top_mem(); break;
            case 6: exit(0);
            default: printf("\nInvalid Choice\n"); break;
        }
    }
}