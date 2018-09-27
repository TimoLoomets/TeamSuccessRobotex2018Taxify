using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Drawing;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace TTÜ_ROBOTEX
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }


        class Information
        {

            void ReadText(string[] args)
            {
                List<Taxy> taxy = new List<Taxy>();
                string filePath = @"C:\Users\enric\Desktop\Sample.txt";
                List<string> lines = File.ReadAllLines(filePath).ToList();
                foreach (var line in lines)
                {
                    string[] entries = line.Split(' ');

                    Taxy newTaxy = new Taxy();

                    newTaxy.Time_string = entries[0];
                    newTaxy.TaxyID_string = entries[1];
                    newTaxy.Latitude_string = entries[2];
                    newTaxy.Lenghtitude_string = entries[3];

                    taxy.Add(newTaxy);
                    
                }

                foreach (var Taxy in taxy) // loops every line in .sample.txt file
                {

                    Ellipse Taxy_location = new Ellipse(taxy[2], taxy[3], 10, 10);
                    

                }
            }
        }
    }
}
