    #include <stdio.h>
    #include <stdlib.h>/*包含system函数*/
    #include <fcntl.h>/*包含open函数*/
    int open_file(char *_filename,int flag,mode_t mode);
    int copy_file(char *_src,char *_des);
    int main(int argc,char **argv)
    {
        copy_file(argv[1],argv[2]);
    }
    /*********************************************************
    ** 函 数 名:int open_file(char *_filename,int flag,mode_t mode)
    ** 功能描述:打开文件明为filename的文件
    ** 输入参数: filename - char* <文件名称>
         flag - int <文件属性>
                flag:
                    O_CREAT <文件不存在时建立文件>
                    O_RDONLY
                    O_WRONLY
                    O_APPEND
                    O_TRUNG <设置文件的长度0，并舍弃现存的数据>
                    O_EXCL <与O_CREAT 一起使用，如果文件存在，则打开失败>
                 mode - mode_t <文件权限>
                mode:
                    0666 <000 110 110 110>
    ** 输出参数:
    ** 返 回 值: - int <打开成功返回文件描述发，失败返回0>
    ** 作 者:<张洪波>
    ** 日 期:2011-5-20
    ** 修 改:<修改人>
    ** 日 期:
    **********************************************************/
    int open_file(char *_filename,int _flag ,mode_t _mode)
    {
        int fd = 0;
        fd = open(_filename,_flag,_mode);
        if(fd < 0)
        {
            perror("Open file error");
        }
        return fd;
        
    }
    /*********************************************************
    ** 函 数 名:int copy_file(char *_src,char *_des)
    ** 功能描述:模拟linux的cp命令，实现文本文件的拷贝
    ** 输入参数: _src - char* <源文件名称>
                           _des - char* <目标文件名称>
    ** 输出参数: x - 类型 <说明>
    ** 返 回 值: - int <成功返回1，失败返回0>
    ** 作 者:<张洪波>
    ** 日 期:
    ** 修 改:<修改人>
    ** 日 期:
    **********************************************************/
    int copy_file(char *_src,char *_des)
    {
        int src_flags = O_RDONLY;
        int des_flags = O_CREAT | O_TRUNC | O_WRONLY;
        int src_fd = open_file(_src,src_flags,0666);
        int des_fd = open_file(_des,des_flags,0777);
        char buf[100];
        int nbytes;//每次读取的字节个数
        int write_ret;
        /*读文件，写文件*/
        
        while(nbytes = read(src_fd,buf,100))/*每次从源文件读取100字节数据到buf*/
        {
            //printf("%d\n",nbytes);
            write_ret = write(des_fd,buf,nbytes);/*将buf中的数据写入目标文件*/
            if(write_ret < 0)
            {
                perror("Write error");
                exit(1);
            }
        }
        close(src_flags);
        close(des_flags);
        printf("复制文件%s到%s成功!\n",_src,_des);
    }