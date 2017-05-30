using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using Windows.ApplicationModel.AppService;
using Windows.Foundation.Collections;
using System.Diagnostics;

namespace WinFormsApp
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            SetupAppService();
            Application.Run(new Form1());
        }


        static async void SetupAppService()
        {
            Trace.WriteLine("AppService OSC: Starting...");
            AppServiceConnection connection = new AppServiceConnection();
            connection.AppServiceName = "MyCustomAppServiceMuse";
            connection.PackageFamilyName = Windows.ApplicationModel.Package.Current.Id.FamilyName;

            var result = await connection.OpenAsync();
            if (result == AppServiceConnectionStatus.Success)
            {
                Trace.WriteLine("AppService OSC: Got success connection from UWP");

                // Setup a request handler to have two way communication with UWP.
                // Basically, this will recevie OSC messages from UWP
                connection.RequestReceived += Connection_RequestReceived;

                // Send a message to UWP app
                var dummy = new ValueSet();
                var res = await connection.SendMessageAsync(dummy);

                if (res.Status == AppServiceResponseStatus.Success)
                {
                    Trace.WriteLine("AppService OSC: Got success response from UWP");
                }
                else
                {
                    Trace.WriteLine("AppService OSC: Res code is " + res.Status.ToString());
                }
            }
            else
            {
                Trace.WriteLine("AppService OSC: ERROR");
            }
        }

        private static void Connection_RequestReceived(AppServiceConnection sender, AppServiceRequestReceivedEventArgs args)
        {
            //Trace.WriteLine("AppService OSC: Request hander called in WinForm");            
            
            var msg = args.Request.Message;            
            osc_handler_.HandleMessage(msg);

            //var deferral = args.GetDeferral();
            //deferral.Complete();
        }

        private static OscManager osc_handler_ = new OscManager();
    }
}
