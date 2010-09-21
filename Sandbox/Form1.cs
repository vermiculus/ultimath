using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Sandbox
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public void Output(string s)
        {
            txtOut.Text += s;
        }
        private void btnSubmit_Click(object sender, EventArgs e)
        {
            //MessageBox.Show("You clicked my button!");
            Output("Testing begun. " + DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToLongTimeString() + "\r\nInput: " + '"' + txtIn.Text + '"' + "\r\n");

            ////
            Function func = new Function(txtIn.Text, 'x');
            foreach (Function.Arg_Part a in func.arg_list)
                Output(a.value + " " + a.classification.ToString() + "\r\n\r\n");
            ////

            Output("Testing complete.\r\n\r\n");
        }
    }
}
