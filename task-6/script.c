#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    if (argc!=2){
        printf("Синтаксис команды: %s filepath\n", argv[0]); 
        exit(1); 
    }
    struct stat *buf;
    if (stat (argv[1], buf)==0){
        printf("Информация о файле:\n");
        printf(" - Режим файла: %d\n", buf->st_mode);
        printf(" - Номер описателя файла: %d\n", buf->st_ino);
        printf(" - Идент. устройства, содержащего каталог с входом в этот файл: %d\n", buf->st_dev);
        //printf("Идент.  устройства", buf->st_rdev); определено только лдля специальных ил  блочных файлов
        printf(" - Количество ссылок: %d\n", buf->st_nlink);
        printf(" - Идент. владельца файла: %d\n", buf->st_uid);
        printf(" - Идент. группы владельца файла: %d\n", buf->st_gid);
        printf(" - Размер файла: %d байт\n",buf->st_size);
        //printf(" - Время последнего доступа к файлу: %d\n", buf->st_atime);
        //printf(" - Время последней записи в файл: %d\n", buf->st_mtime);
        //printf(" - Время  последнего изменения статуса файла: %d\n", buf->st_ctime);
    }else {
        perror("Ошибка");
    }
    
    

    return 0;
}