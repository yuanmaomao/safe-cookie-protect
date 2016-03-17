using System.Collections.Generic;
using System.Windows;
using System.Windows.Documents;
using System.Windows.Input;
using System.IO;
using System.Linq;
using System;

namespace WpfCookies
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 列表的双击
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LVC_MouseDoubleClick(object sender, MouseButtonEventArgs e)
            //单击listview，可查看cookis内容
        {
            var c = LVC.SelectedItem as cookie;
            tbcookie.Text = c.text;
        }

        /// <summary>
        /// 刷新按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Button_Click(object sender, RoutedEventArgs e)//选择浏览器进行查看
        {


            if (bro.SelectedItem == "IE")
            {
                cookies = new List<cookie>();
                getIECookies(IEPath);
                this.LVC.ItemsSource = cookies;
            }
            else if (bro.SelectedItem == "Chrome")
            {
                cookies = new List<cookie>();
                getChromeCookies(ChromePath);
                this.LVC.ItemsSource = cookies;
            }
            else
            {
                showAll();
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)//删除按钮，根据需要删除
        {
            switch (select.SelectedIndex)
            {
                case 0:
                    {
                        var count = from cook in cookies
                                    where cook.isselect == true
                                    select cook;
                        int p = 0;
                        foreach (var item in count)
                        {
                            p++;
                        }
                        if (p > 0)
                        {
                            foreach (var item in cookies)
                            {
                                if (item.isselect)
                                {
                                    delcookie(item);
                                }
                            }
                        }
                        else
                        {
                            System.Windows.MessageBox.Show("未选中！");
                        }
                        break;
                    }
                case 1:
                    {
                        foreach (var item in cookies)
                        {
                            if (item.isOverDue)
                            {
                                delcookie(item);
                            }
                        }
                        break;
                    }
                case 2:
                    {
                        List<string> websites = new List<string>();
                        string listpath = "list.txt";
                        if (File.Exists(listpath))
                        {
                            StreamReader ls = File.OpenText(listpath);
                            string line;
                            while ((line = ls.ReadLine()) != null)
                            {
                                websites.Add(line);
                            }
                            ls.Close();
                            for (int i = 0; i < cookies.Count; i++)
                            {
                                foreach (var web in websites)
                                {
                                    if (cookies[i].site.Contains(web))
                                    {
                                        cookies[i].islist = true;
                                    }
                                }
                            }
                            foreach (var c in cookies)
                            {
                                if (!c.islist)
                                {
                                    delcookie(c);
                                }
                            }
                        }
                        else
                        {
                            System.Windows.MessageBox.Show("未设置白名单！");
                        }

                        break;
                    }
                case 3:
                    {
                        foreach (var item in cookies)
                        {
                            delcookie(item);
                        }
                        break;
                    }
                default:
                    break;
            }
            Button_Click(sender, e);
            tbcookie.Text = " ";

        }

        private void Button_Click_2(object sender, RoutedEventArgs e)//白名单窗口
        {
            list listwin = new list();
            listwin.ShowDialog();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)//窗体载入时
        {
            if (!File.Exists("list.txt"))
            {
                File.Create("list.txt");
            }
            //if (!File.Exists("user.ini"))
            //{

            //    File.WriteAllText("user.ini", "false");
            //    File.SetAttributes("user.ini", FileAttributes.System | FileAttributes.Hidden);
            //}
            getPath();
            System.Windows.MessageBox.Show("建议关闭浏览器使用……");
            getBrowser();

        }

        private void Button_Click_3(object sender, RoutedEventArgs e)//游客模式
        {
            System.Windows.MessageBox.Show("此功能暂时只针对xp上的IE,并容易出错！");
            if (Environment.OSVersion.Version.Major < 6)
            {
                proc("Login.exe");
            }
        }

        private void Button_Click_4(object sender, RoutedEventArgs e)//Chrome格式查看
        {
            iamge img = new iamge("resources/Chrome1.png");
            img.Show();
        }

        private void Button_Click_5(object sender, RoutedEventArgs e)//IE格式查看
        {
            iamge img = new iamge("resources/ie1.png");
            img.Show();
        }

        private void btch1_Click(object sender, RoutedEventArgs e)//主模式
        {
            System.Windows.MessageBox.Show("此功能暂时只针对xp上的IE,并容易出错！");
            if (Environment.OSVersion.Version.Major < 6)
            {
                proc("Logout.exe");
            }
        }
    }
}
