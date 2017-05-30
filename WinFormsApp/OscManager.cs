using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Foundation.Collections;
using System.Diagnostics;
using SharpOSC;

namespace WinFormsApp
{
    class OscManager
    {
        public void HandleMessage(ValueSet msg)
        {
            //var data = msg["count"]; // Try getting the msg but do nothing
            var count = "Receiving: " + msg["count"].ToString();
            Trace.WriteLine(count);
            //SendOsc();
        }

        // Don't even need to call this method to reproduce memory leak
        private void SendOsc()
        {
            // Send dummy data to OSC
            var data = new List<object>();
            data.Add(23.45f);
            data.Add(44.23f);
            data.Add(243.43f);
            data.Add(32.30f);
            data.Add(12.34f);
            
            var message = new OscMessage("osc/test", data);
            sender_.Send(message);
        }

        // Send data on localhost port 50000
        private UDPSender sender_ = new UDPSender("127.0.0.1", 50000);
    }
}
