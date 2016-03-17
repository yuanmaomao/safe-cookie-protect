using System;
using System.IO;
namespace WpfCookies
{
    public class cookie
    {
        /// <summary>
        /// cookies类，绑定的数据源，以及获取IEcookies的内容操作也此定义
        /// </summary>
        public string name { get; set; }
        public string timeWrite { get; set; }//最后写入时间
        public string time { get; set; }//过期时间
        public string site { get; set; }
        public string text { get; set; }
        public string version { get; set; }//浏览器版本
        public string value { get; set; }//cookis值
        public string path { get; set; }
        public bool islist { get; set; }//是否在白名单中
        public bool isselect { get; set; }   //是否选中 
        public string localtime
        {
            get
            {
                if (version == "chrome")
                {
                    if (time == "0")
                    {
                        return "长期有效";
                    }
                    string s = time + "0";
                    long t = Convert.ToInt64(s);
                    DateTime dt = DateTime.FromFileTime(t);
                    return dt.ToShortDateString();
                }
                else
                {
                    long t = Convert.ToInt64(time);
                    DateTime dt = DateTime.FromFileTime(t);
                    return dt.ToShortDateString();
                    return time;
                }
            }
        }//转化为可辨认时间
        public string localtimewrite
        {
            get
            {
                if (version == "ie")
                {
                    return timeWrite;
                }
                else
                {
                    string s = timeWrite + "0";
                    long t = Convert.ToInt64(s);
                    DateTime dt = DateTime.FromFileTime(t);
                    return dt.ToShortDateString();
                }
            }
        }
        public bool isOverDue
        {
            get
            {
                if (time != "0")
                {
                    if (version == "chrome")
                    {
                        if (Convert.ToInt64(time + "0") > DateTime.Now.ToFileTime())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        if (Convert.ToInt64(time) > DateTime.Now.ToFileTime())
                        {
                            return false;
                        }
                    }
                }
                return true;
            }
        }//是否过期
        public void getCookieInfo(string path, out string Time,
                                  out string Site, out string text1)//获取IEcookis内容
        {
            StreamReader sr = File.OpenText(path);
            string nextLine;
            value = sr.ReadLine();
            nextLine = sr.ReadLine();
            Site = sr.ReadLine();
            sr.ReadLine();
            nextLine = sr.ReadLine();
            string nextLine2 = sr.ReadLine();
            Int64 t;
            t = Convert.ToInt64(nextLine2);
            t = t << 32;
            t = t + Convert.ToInt64(nextLine);
            Time = t.ToString();//时间判断:此处参见http://www.cnblogs.com/-clq/archive/2011/12/01/2271134.html
            sr.Close();
            StreamReader sr1 = File.OpenText(path);
            text1 = sr1.ReadToEnd();
            sr1.Close();
        }
    } 
}
