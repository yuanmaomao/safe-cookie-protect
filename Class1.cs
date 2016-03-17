using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Data.SQLite;
namespace WpfCookies
{
    /// <summary>
    /// 分部类
    /// </summary>
    public partial class MainWindow : Window
    {
        List<cookie> cookies;
        string IEPath;
        string ChromePath;
        /// <summary>
        /// 根据系统版本获取不同的路径。
        /// </summary>
        public void getPath()
        {
            if (Environment.OSVersion.Version.Major > 5)
            {
                IEPath = "C:\\Users\\" + Environment.UserName + "\\AppData\\Roaming\\Microsoft\\Windows\\Cookies";
                ChromePath = "C:\\Users\\" + Environment.UserName + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default";
            }
            else
            {
                IEPath = "C:\\Documents and Settings\\" + Environment.UserName + "\\Cookies";
                ChromePath = "C:\\Documents and Settings\\" + Environment.UserName + "\\Local Settings\\Application Data\\Google \\Chrome\\User Data\\Default";
            }
        }
        /// <summary>
        /// 获取IE的cookis
        /// </summary>
        /// <param name="path"></param>
        public void getIECookies(string path)
        {
            List<FileInfo> list = new List<FileInfo>();
            DirectoryInfo d = new DirectoryInfo(path);
            DirectoryInfo[] dc = d.GetDirectories();
            FileInfo[] fs = d.GetFiles("*.txt");
            list.AddRange(fs);
            foreach (var item in dc)
            {
                fs = item.GetFiles("*.txt");
                list.AddRange(fs);
            }
            foreach (var item in list)
            {
                cookie ct = new cookie();
                ct.name = item.Name;
                ct.timeWrite = item.LastWriteTime.ToShortDateString();
                ct.path = item.DirectoryName;
                String t = ct.path + "\\" + item.Name;
                string time;
                string site;
                string text;
                ct.getCookieInfo(t, out time, out site, out text);
                ct.time = time;
                ct.site = site;
                ct.text = text;
                ct.version = "ie";
                cookies.Add(ct);
            }
        }
        public void delIECookie(string path)
        {
            File.Delete(path);
        }
        /// <summary>
        /// 获取Chrome的cookies，sqlite3数据库
        /// </summary>
        /// <param name="path"></param>
        public void getChromeCookies(string path)
        {
            string t = "Data Source=" + path + "\\Cookies";
            SQLiteConnection sqlcon = new SQLiteConnection(t);
            sqlcon.Open();
            SQLiteCommand cmd = new SQLiteCommand();
            cmd.CommandText = "SELECT * FROM cookies";
            cmd.Connection = sqlcon;
            SQLiteDataReader reader = cmd.ExecuteReader();
            while (reader.Read())
            {
                cookie ct = new cookie();
                ct.name = reader.GetString(2);
                ct.value = ct.name;
                ct.timeWrite = reader.GetInt64(8).ToString();
                ct.time = reader.GetInt64(5).ToString();
                ct.site = reader.GetString(1);
                ct.text = reader.GetInt64(0).ToString() + "\r\n" + reader.GetString(1) + "\r\n" +
                          reader.GetString(2) + "\r\n" + reader.GetString(3) + "\r\n" + reader.GetString(4)
                              + "\r\n" + reader.GetInt64(5).ToString() + "\r\n" + reader.GetInt64(6).ToString() + "\r\n" +
                              reader.GetInt64(7).ToString() + "\r\n" + reader.GetInt64(8).ToString() + "\r\n" +
                              reader.GetInt64(9).ToString();
                ct.version = "chrome";
                cookies.Add(ct);
            }
            sqlcon.Close();
        }
        public void delChromeCookies(string name, string value, string path)
        {
            string t = "Data Source=" + path + "\\Cookies";
            SQLiteConnection sqlcon = new SQLiteConnection(t);
            sqlcon.Open();
            SQLiteCommand cmd = new SQLiteCommand();
            cmd.CommandText = "delete from cookies where name= '" + name + "' and expires_utc= '" + value + "'";
            cmd.Connection = sqlcon;
            cmd.ExecuteNonQuery();
            sqlcon.Close();
        }
        public void getBrowser()
        {
            cookies = new List<cookie>();
            if (Directory.Exists(IEPath))
            {
                ms.Visibility = Visibility.Visible;
                bro.Items.Add("IE");
                getIECookies(IEPath);
            }
            if (File.Exists(ChromePath + "\\Cookies"))
            {
                google.Visibility = Visibility.Visible;
                bro.Items.Add("Chrome");
                getChromeCookies(ChromePath);
            }
            this.LVC.ItemsSource = cookies;
            if (cookies.Count == 0)
            {
                System.Windows.MessageBox.Show("没有cookies");
            }
        }//获取浏览器，加载图片
        public void delcookie(cookie c1)
        {
            if (c1.version == "ie")
            {
                string path = c1.path + "\\" + c1.name;
                delIECookie(path);
            }
            if (c1.version == "chrome")
            {
                delChromeCookies(c1.name, c1.time, ChromePath);
            }
        }
        public void showAll()
        {
            cookies = new List<cookie>();
            if (Directory.Exists(IEPath))
            {
                getIECookies(IEPath);
            }
            if (File.Exists(ChromePath + "\\Cookies"))
            {
                getChromeCookies(ChromePath);
            }
            this.LVC.ItemsSource = cookies;
            if (cookies.Count == 0)
            {
                System.Windows.MessageBox.Show("没有cookies");
            }
        }//所有cookis获取
        public void proc(string pro)
        {
            string path = pro;//这个path就是你要调用的exe程序的绝对路径
            System.Diagnostics.Process process = new System.Diagnostics.Process();
            process.StartInfo.FileName = pro;
            process.StartInfo.WorkingDirectory = path;
            process.StartInfo.CreateNoWindow = true;
            process.Start();
            if (process.HasExited)
            {
                MessageBox.Show("已切换");
            }
        }//模式切换所需的进程
    }
}
