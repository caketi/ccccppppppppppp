``` c

// 端口-- 指定端口
// 进程名称检测 手动值0
// filecheck 关键文件检测-- 绕过-改名
//  ps | grep  [target]
//  cat /proc/[pid]/status
sprintf(filename, "/proc/%d/status", pid);
File *fd = fopen(filename, "r");
if(fd != NULL){
    while(fgets(line, bufsize, fd)){
        if(strstr(line, "TracePid") != NUL){
            int statue = atoi(&line[10]);
            if(statue != 0){
                sprintf(name, "/proc/.%d/cmdline", statue);
                FILE *fdname = fopen(name, "r");
                if(fdname != NULL){
                    while(fgets(nameline, bufsize, fdname)){
                        if(strstr(nameline, "android_server")!=-NULL){
                            int ret = kill(pid, SIGKILL);
                        }
                    }
                }
                fclose(fdname);
            }
        }
    }
}
fclose(fd);

void check(){
    const char* rootPath = "/data/local/tmp";
    DIR* dir;
    dir = opendir(rootPath);
    int pid = getpid();
    if(dir != NULL){
        dirent *currentDir;
        while((currentDir = readdir(dir)) != NULL){
            // 存在android_server -- Killed
            // readdir() 类似 java中的迭代器next()
            //currentDir->d_name文件名 目录名  currentDir->d_name 类型 目录？文件
            if(strncmp(currentDir->d_name, "android_server", 14) == 0){
                printf("%s", currentDir->d_name);
                kill(pid, SIGKILL);
            }
        }
        closedir(dir);
    }else{}
}
```