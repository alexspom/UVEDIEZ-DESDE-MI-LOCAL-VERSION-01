using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace v10browser
{
    public partial class Form1 : Form
    {

        public Form1()
        {

            InitializeComponent();

            string ip="";
            string puerto="";
            string hostname="";
            string extra="";
            string tipocon = "http";
            string url = "";

            //Para bien o para mal, by pibe 30/05/2017

           string[] args = Environment.GetCommandLineArgs();

           if (args.Length < 2) {
               MessageBox.Show("Tienes que crear un acceso directo y pasar como parámetros de entrada, \nla IP PUERTO EXTRAS, al menos, los dos primeros son necesarios, el resto\n rellenar con comillas! \n\nv10browser.exe 192.168.1.209 5000 ''","V10Browser");
               Environment.Exit(0);
           }
            else {
               ip = args[1]; //ip de conexión como parámetro
               puerto = args[2]; //puerto de conexión como parámetro
               hostname = System.Windows.Forms.SystemInformation.ComputerName; // saco el hostname a saco.
               extra = args[3]; // extras para la cadena de conexión
               if (args.Length > 4) tipocon = args[4];
           }
           url = tipocon + "://" + ip + ":" + puerto + "/v10LOGIN/&HOST=" + hostname + "&EXTRA=" + extra + "&";

            webBrowser1.Url = new System.Uri(tipocon+"://" + ip + ":" + puerto + "/v10LOGIN/&HOST=" + hostname + "&EXTRA=" + extra + "&", System.UriKind.Absolute);

            this.webBrowser1.DocumentTitleChanged += new EventHandler(webBrowser1_DocumentTitleChanged); //cojo el primer valor del titulo y si cambia más adelante lo capturo y actualizo.

        }

        void webBrowser1_DocumentTitleChanged(object sender, EventArgs e)
        {
            this.Text = "V10 Browser - " + this.webBrowser1.DocumentTitle;
        }

        
    }
}
