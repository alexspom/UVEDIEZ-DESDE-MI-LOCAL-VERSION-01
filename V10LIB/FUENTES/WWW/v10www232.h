
// funciones equivalentes a las definidas en el módulo 232W32, para manejar un puerto serie remotamente
// (mediante un puente TCPIP)
V10IMPORT int	v10wwwinitpuerto232(int com,int velocidad,int paridad,int bits,int parada);
V10IMPORT void  v10wwwclosepuerto232(int com);
V10IMPORT void  v10fin232(void);

V10IMPORT void	v10wwwpon232(int com,long velocidad,int paridad,int stop,int bits);


V10IMPORT void	v10wwwst232(int puerto,long *velocidad,int *paridad,int *parada,int *datos);
V10IMPORT void  v10wwwprotocolo232(int port,int xon);

V10IMPORT void	v10wwwencolae(int com,int ch);
V10IMPORT void	v10wwwencolaec(int com,char *cadena);


V10IMPORT int	v10eeehaycar232(int com);
V10IMPORT int	v10wwwsig_carr(int com);
V10IMPORT void  v10wwwprintf232(int com,char *format,...);
V10IMPORT DWORD v10wwwwritebuffer232(int com,void *msg, int tam);

V10IMPORT int	v10wwwhaypuerto232(void);
V10IMPORT void	v10wwwisinit232(void);
V10IMPORT int   v10wwwponinit232(int puerto,int ret);





