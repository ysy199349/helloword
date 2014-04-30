#include<dirent.h>
#include<stdio.h>
#include<string.h>
void main()
{
    DIR *dir;
    struct dirent *ptr;
    FILE *fp;
    char filepath[50];//大小随意，能装下cmdline文件的路径即可
    char filetext[50];//大小随意，能装下要识别的命令行文本即可
    dir = opendir("/proc"); //打开路径
    if (NULL != dir)
    {
        while ((ptr = readdir(dir)) != NULL) //循环读取路径下的每一个文件/文件夹
        {
            //如果读取到的是"."或者".."则跳过，读取到的不是文件夹名字也跳过
            if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0)) continue;
            if (DT_DIR != ptr->d_type) continue;
           
            sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);//生成要读取的文件的路径
            fp = fopen(filepath, "r");//打开文件
            if (NULL != fp)
            {
                fread(filetext, 1, 50, fp);//读取文件
                filetext[49] = '\0';//给读出的内容加上字符串结束符
                //如果文件内容满足要求则打印路径的名字（即进程的PID）
                if (filetext == strstr(filetext, "./test")) printf("PID:  %s\n", ptr->d_name);
                fclose(fp);
            }
           
        }
        closedir(dir);//关闭路径
    }
}
