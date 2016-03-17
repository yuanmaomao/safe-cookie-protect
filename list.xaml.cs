using System.Windows;
using System.IO;
namespace WpfCookies
{
    /// <summary>
    /// list.xaml 的交互逻辑
    /// </summary>
    public partial class list : Window
    {
        string path = "list.txt";
        public list()
        {
            InitializeComponent();
            tb.Text = File.ReadAllText(path);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            File.WriteAllText(path, tb.Text);
        }
    }

}
