#include<stdio.h>
#include<unistd.h>
int main()
{
    int choice,f;
    printf("1.Fork 1\n2.Fork 2\nENTER CHOICE: ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            f=fork();
            if(f==0)
            {
                printf("Child process C1 created with process id %d and parent id %d\n",getpid(),getppid());
                f=fork();
                if(f==0)
                    printf("Child process C3 created with process id %d and parent id %d\n",getpid(),getppid());
                else if(f>0)
                {
                    f=fork();
                    if(f==0)
                        printf("Child process C4 created with process id %d and parent id %d\n",getpid(),getppid());
                }
            }
            else if(f>0)
            {
                printf("This is the parent process P with id %d\n",getpid());
                f=fork();
                if(f==0)
                    printf("Child process C2 created with process id %d and parent id %d\n",getpid(),getppid());
            }
            break;
        case 2:
            f=fork();
            if(f==0)
                printf("Child process C2 created with process id %d and parent id %d\n",getpid(),getppid());
            else if(f>0)
            {
                printf("This is the parent process P with id %d\n",getpid());
                f=fork();
                if(f==0)
                {
                    printf("Child process C1 created with process id %d and parent id %d\n",getpid(),getppid());
                    f=fork();
                    if(f==0)
                         printf("Child process C3 created with process id %d and parent id %d\n",getpid(),getppid());

                }
            }
    }
        
    return 0;
}