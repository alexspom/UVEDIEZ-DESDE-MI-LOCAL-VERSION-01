// C#



using System;
using System.IO;
using System.Data;
using System.Data.Common;
using System.Threading;
using Oracle.DataAccess.Client;
using CrystalDecisions.CrystalReports.Engine;
using CrystalDecisions.Shared;

class v10param
{
    public static string flog;
    public static string usuario;
    public static string user;
    public static string pass; 
    public static string db;
    public static int nivellog = 2;
    public const int LOGERROR = 0;
    public const int LOGWARNING = 1;
    public const int LOGNORMAL = 2;
    public const int LOGDEBUG = 3;
    public static string grupoimpre;
    static DateTime ultlog = DateTime.Now; 
    static System.IO.StreamWriter fichlog;
    public static  void trataparam(string[] args)
    {
        foreach (string Par in args) {
            if (Par[0] == '-') {
                switch (Par[1])  {
                    case 'O': switch (Par[2])
                        {
                            case 'U': usuario = Par.Substring(3);
                                user = usuario.Split('/')[0];
                                pass = usuario.Split(new char []{'/','@'})[1];
                                db=usuario.Split('@')[1];
                                break;
                        }
                        break;
                    case 'L': switch (Par[2])
                        {
                            case 'N': flog = Par.Substring(3);
                                break;
                            case 'M': nivellog = int.Parse( Par.Substring(3));
                                break;
                        }
                        break;
                    case 'I': switch (Par[2])
                        {
                            case 'N': grupoimpre = Par.Substring(3);
                                break;
                        }
                        break;
                }
            }
        }
    }

    public static void Log(int nivel,String cadena)
    {
        DateTime fecha = DateTime.Now;
        if (nivel > v10param.nivellog) return;
        if (fecha.Date != ultlog.Date && fichlog != null)
        {
            fichlog.Close();
            fichlog = null;
        }
        if (fichlog == null) {
            string path;
            path=Environment.GetEnvironmentVariable("DIRLOG");
            if (path!=null) path = path + "\\";
            path=path+ flog+fecha.Year+fecha.Month+fecha.Day+".LOG";
            fichlog=new System.IO.StreamWriter(path,true);
            fichlog.WriteLine(v10param.nivellog+" "+fecha.TimeOfDay.ToString().Substring(0, 12) + " " + "Fichero de log abierto " + fecha.Date.ToString().Substring(0,10));
        }
        fichlog.WriteLine(v10param.nivellog + " " + fecha.TimeOfDay.ToString().Substring(0, 12) + " " + cadena);
        Console.WriteLine(v10param.nivellog + " " + fecha.TimeOfDay.ToString().Substring(0, 12) + " " + cadena);
        fichlog.Flush();
    }

    ~v10param()
    {
        fichlog.Close();
    }
}

class v10report
{
    public ReportDocument rep;
    static OracleCommand dameprinter;
    public v10report(string nombre, string user, string pass, string bd)
    {
        Tables mistablas;
        ConnectionInfo crcon = new ConnectionInfo();
        rep = new ReportDocument();
        rep.FileName = nombre;
        crcon.DatabaseName =bd;
        crcon.ServerName = bd;
        crcon.UserID = user;
        crcon.Password = pass;
        mistablas = rep.Database.Tables;
        foreach (Table i in mistablas) {
            TableLogOnInfo tlog = new TableLogOnInfo();
            tlog = i.LogOnInfo;
            tlog.ConnectionInfo = crcon;
            i.ApplyLogOnInfo(tlog);
        }
    }

    public void imprime(string codimpre,string fichero,int numcopias)
    {
        if (codimpre == "WINFILE") {
            if (fichero.ToUpper().LastIndexOf(".PDF") > 0)
            {
                rep.ExportToDisk(ExportFormatType.PortableDocFormat, fichero);
                return;
            }
            if (fichero.ToUpper().LastIndexOf(".DOC") > 0)
            {
                rep.ExportToDisk(ExportFormatType.WordForWindows, fichero);
                return;
            }
            if (fichero.ToUpper().LastIndexOf(".RTF") > 0)
            {
                rep.ExportToDisk(ExportFormatType.RichText, fichero);
                return;
            }
            if (fichero.ToUpper().LastIndexOf(".HTM") > 0)
            {
                rep.ExportToDisk(ExportFormatType.HTML40, fichero);
                return;
            }
            v10param.Log(v10param.LOGNORMAL,"Error no existe formato para documento " + fichero);
            return;
        }
        if (codimpre == "WINDEF") {

            rep.PrintToPrinter(numcopias, false, 1, 999999);
            return;
        }
        if (codimpre == "WINVIEW")   {

            rep.ExportToDisk(ExportFormatType.PortableDocFormat, "PRUEBA1.PDF");
            return;
        }
        if (dameprinter == null)
        {
            dameprinter = new OracleCommand("SELECT FICHERO FROM VDIMPRESORAS WHERE CODIMPRE=:CODIMPRE", v10oracle.conn); ;
            dameprinter.Parameters.Add("CODIMPRE", OracleDbType.Varchar2, ParameterDirection.Input);
        }
        String impresora;
        dameprinter.Parameters["CODIMPRE"].Value = codimpre;
        impresora=dameprinter.ExecuteScalar().ToString();
        rep.PrintOptions.PrinterName = impresora;
        rep.PrintToPrinter(numcopias, false, 1, 999999);
        rep.Dispose();
        return;
      }

    public void ponparam(string parametros)
    {
        string[] parametro;
        parametro = parametros.Split(';');
        foreach (string par in parametro)
        {
            string variable, valor;
            variable = par.Split('=')[0];
            valor = par.Split('=')[1];
            try
            {
                rep.SetParameterValue(variable, valor);
            }
            catch
            {
                rep.DataDefinition.FormulaFields[variable].Text = "'"+valor+"'";
            }
        }
    }
}

class fichero {
    public struct  caches {
        public string nombre;
        public string path;
    };
    public static caches[] cache;
    public static int nelem = 0;

    public static string nombrecompleto(string nombre)
    {
        int i;
        for (i=0;i<nelem;i++) {
            if (nombre.ToUpper()==cache[i].nombre) return(cache[i].path+"\\"+nombre);
        }
        return null;
    }

    public static void expandpath(string path)
    {
        DirectoryInfo dir = new DirectoryInfo(path);
        foreach (FileInfo flInfo in dir.GetFiles())
        {
            caches uno=new caches();
            uno.nombre = flInfo.Name.ToUpper();
            uno.path = path;
            cache.SetValue(uno, nelem++);
        }
        string[] directories = Directory.GetDirectories(path);
        foreach (string nuevodir in directories)
        {
            expandpath( nuevodir);
        }
    }

    public static void rellenacache(string v10path)
    {
        String[] componente;
        cache=new caches[200000];
        componente=v10path.Split(';');
        foreach (string comp in componente)
        {
            expandpath(comp);
        }
    }
}


class v10oracle
{
//    static DbProviderFactory factory;
    public static OracleConnection conn;

    public static void conecta()
    {
//        factory = DbProviderFactories.GetFactory("Oracle.DataAccess.Client");
        conn = new OracleConnection();
        conn.ConnectionString = "User Id=" + v10param.user + "; Password=" + v10param.pass + "; Data Source=" + v10param.db + ";";
        conn.Open();
    }

}

class ejecutacrystal
{
    public struct informes
    {
        public string codimpre;
        public string fichero;
        public string parcial;
        public string report;
        public string param;
        public int seqimpre;
    }

    static public void procesafichero(object data)
    {
        informes inf = (informes)data;
        OracleCommand updafin = new OracleCommand("UPDATE VDIMPRESPOOL SET STATUS=VDST.FISPFINALIZADA WHERE SEQIMPRE=:SEQIMPRE", v10oracle.conn);
        updafin.Parameters.Add("SEQIMPRE", OracleDbType.Decimal, ParameterDirection.Input);
        updafin.Parameters["SEQIMPRE"].Value = inf.seqimpre;
        if (inf.fichero == null)
        {
            updafin.ExecuteNonQuery();
            v10param.Log(v10param.LOGNORMAL,"No existe report " + inf.parcial);
            return;
        }
        v10report rep = new v10report(inf.report, v10param.user, v10param.pass, v10param.db);
        rep.ponparam(inf.param);
        rep.imprime(inf.codimpre,inf.fichero, 1);
        v10param.Log(v10param.LOGNORMAL, "Registro " + inf.seqimpre + " Codimpre " + inf.codimpre + " Informe " + inf.parcial + " Parametros " + inf.param);
        updafin.ExecuteNonQuery();
    }

  static void Main(string[] args)
    {
        Console.BackgroundColor = ConsoleColor.Blue;
        Console.ForegroundColor = ConsoleColor.White;
        v10param.Log(v10param.LOGNORMAL, "Inicio");

    v10param.trataparam(args);
    v10oracle.conecta();
    v10param.Log(v10param.LOGNORMAL, "Conectado a base de datos " + v10param.user + "@" + v10param.db);
    v10param.Log(v10param.LOGNORMAL, "Procesando grupos " + v10param.grupoimpre);
    fichero.rellenacache(Environment.GetEnvironmentVariable("PATHV10"));
    OracleCommand com = new OracleCommand("SELECT * FROM VDIMPRESPOOL WHERE STATUS=VDST.FISPPENDIENTE AND CODIMPRE IN (SELECT CODIMPRE FROM VDIMPRESORAS WHERE VD.CONTIENE(:GRUPOIMPRE,GRUPOIMPRE)>0)", v10oracle.conn);
    com.Parameters.Add("GRUPOIMPRE", OracleDbType.Varchar2, ParameterDirection.Input);
    com.Parameters["GRUPOIMPRE"].Value = v10param.grupoimpre;
      try
      {
          while (true)
          {
              OracleDataReader reader = com.ExecuteReader();
              while (reader.Read())
              {
                  informes inf;
                  Thread mithread = new Thread(ejecutacrystal.procesafichero);
                  inf.seqimpre = int.Parse(reader["SEQIMPRE"].ToString());
                  inf.codimpre = reader["CODIMPRE"].ToString();
                  inf.parcial = reader["DOCUMENTO"].ToString();
                  inf.report=fichero.nombrecompleto(inf.parcial);
                  inf.fichero =  reader["FICHERO"].ToString();
                  inf.param = reader["PARAMS"].ToString();
                  v10param.Log(v10param.LOGNORMAL, "Registro " + inf.seqimpre + " Codimpre " + inf.codimpre + " Informe " + inf.parcial + " Parametros " + inf.param);
                  if (inf.report == null)
                  {
                      v10param.Log(v10param.LOGNORMAL, "Registro " + inf.seqimpre + " Codimpre " + inf.codimpre + " Informe " + inf.parcial + " No existe");

                  }
                  else
                  {
                      mithread.Start(inf);
                  }
                  OracleCommand updainter = new OracleCommand("UPDATE VDIMPRESPOOL SET STATUS=VDST.FISPESPCOMUNIC WHERE SEQIMPRE=:SEQIMPRE", v10oracle.conn);
                  updainter.Parameters.Add("SEQIMPRE", OracleDbType.Decimal, ParameterDirection.Input);
                  updainter.Parameters["SEQIMPRE"].Value = inf.seqimpre;
                  updainter.ExecuteNonQuery();
              }
              reader.Dispose();
              if (Console.KeyAvailable)
              {
                  System.ConsoleKeyInfo ch = Console.ReadKey(true);
                  if (ch.Key == ConsoleKey.F10 && ch.Modifiers == ConsoleModifiers.Alt) break;
                  v10param.Log(v10param.LOGNORMAL, "pulsada tecla " + ch.Key + " " + ch.KeyChar + " " + ch.Modifiers);
              }

              Thread.Sleep(100);
          }

      }
      catch (Exception ex)
      {
        Console.WriteLine(ex.Message);
        Console.WriteLine(ex.StackTrace);
      }
    }
}

