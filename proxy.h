
#if defined(OS_ANDROID)
#include <android/log.h>
 
#define LOG(fmt...) __android_log_print(ANDROID_LOG_DEBUG,__FILE__,##fmt)
 
#else
#define LOG(fmt...)  do { fprintf(stderr,"%s %s ",__DATE__,__TIME__); fprintf(stderr, ##fmt); } while(0)
#endif


char remote_host[128]; 
int remote_port; 
int local_port;
int server_sock; 
int client_sock;
int remote_sock;
char* header_buffer ;
enum 
{
    FLG_NONE = 0,       /* 正常数据流不进行编解码 */
    R_C_DEC = 1,        /* 读取客户端数据仅进行解码 */
    W_S_ENC = 2         /* 发送到服务端进行编码 */
};

static int io_flag; /* 网络io的一些标志位 */
static int m_pid; /* 保存主进程id */

void server_loop();
void stop_server();
void handle_client(int client_sock, struct sockaddr_in client_addr);
void forward_header(int destination_sock);
void forward_data(int source_sock, int destination_sock);
void rewrite_header();
int send_data(int socket,char* buffer,int len );
int receive_data(int socket, char* buffer, int len);
void hand_mproxy_info_req(int sock,char* header_buffer) ;
void get_info(char* output);
const char* get_work_mode() ;
int create_connection() ;
int _main(int argc, char* argv[]) ;

int is_empty_line(char* line) {
    return strcmp(line,"\r\n") == 0 
    || strcmp(line,"\n") == 0;
}

void print_usage(void)
{
    printf("Usage:\n");
    printf(" -l <port number>  specifyed local listen port \n");
    printf(" -h <remote server and port> specifyed next hop server name\n");
    printf(" -d <remote server and port> run as daemon\n");
    printf("-E encode data when forwarding data\n");
    printf ("-D decode data when receiving data\n");
    exit (8);
}

