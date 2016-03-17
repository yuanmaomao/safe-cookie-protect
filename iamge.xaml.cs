using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WpfCookies
{
    /// <summary>
    /// iamge.xaml 的交互逻辑
    /// </summary>
    public partial class iamge : Window
    {
        string path;
        public iamge(string source)
        {
            InitializeComponent();
            path = source;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            image.Source = new BitmapImage(new Uri(path, UriKind.Relative));
        }

    }
}
