#include <bits/stdc++.h>
// #include <windows.h>
using namespace std;
using namespace chrono;
#define loop(n) for (int _n = n; _n; _n--)
#define all(x) (x).begin(), (x).end()
const int N = 2e5 + 5;
char buf[N];
struct Contest {
  // 比赛平台
  string platform;
  // 比赛链接
  string link;
  // 时间点
  tm start_time;
  int start_second;
  // 持续时间
  // int length;
  int hour, minute;
  // 比赛名称
  string name;
// 开始时间：日期+星期+时间
// 比赛名称：同名（在点击比赛名称时，以新建窗口的方式，跳转到对应页面）
// 持续时间：同名
};
void print_tm(tm t) {
  cout << "tm:" << endl;
  cout << t.tm_sec << endl;
  cout << t.tm_min << endl;
  cout << t.tm_hour << endl;
  cout << t.tm_mday << endl;
  cout << t.tm_mon << endl;
  cout << t.tm_year << endl;
  cout << t.tm_wday << endl;
  cout << t.tm_yday << endl;
  cout << t.tm_isdst << endl;
}
vector<Contest> cts;
void get_codeforces_contest() {
  system("D:/Program/anaconda4/python.exe E:/oj_contest_calendar/get_html.py https://mirror.codeforces.com/contests E:/oj_contest_calendar/codeforces.html");
  string txt;
  ifstream f("codeforces.html");
  loop(1000) {
    f.getline(buf, N);
    txt += buf, txt += '\n';
  }
  f.close();
  regex base_regex("<tr data-contestid.*[\\s]*<td.*\\n(.*)[\\s\\S]*? target=\"_blank\">[\\s]*([^<]*)[\\s\\S]*?<td.*[\\s]*(.*)");
  smatch base_match;
  string::const_iterator it = txt.begin();
  while (regex_search(it, txt.cend(), base_match, base_regex)) {
    // for (int i = 1; i < base_match.size(); i++)
    //   cout << base_match[i].str() << endl;
    Contest ct = {};
    ct.platform = "Codeforces";
    ct.link = "https://mirror.codeforces.com/contests";
    stringstream(base_match[2]) >> get_time(&ct.start_time, "%b/%d/%Y %H:%M");
    ct.start_second = mktime(&ct.start_time);
    sscanf(string(base_match[3]).c_str(), "%d:%d", &ct.hour, &ct.minute);
    ct.name = base_match[1];
    cts.push_back(ct);
    // strftime(buf, N, "%Y-%m-%d(%a) %H:%M", &ct.start_time);
    // cout << buf << endl;
    // strftime(buf, N, "%H:%M", &ct.length);
    // cout << buf << endl;
    it = base_match[0].second;
  }
}
void get_atcoder_contest() {
  system("D:/Program/anaconda4/python.exe E:/oj_contest_calendar/get_html.py https://atcoder.jp/contests/ E:/oj_contest_calendar/atcoder.html");
  string txt;
  ifstream f("atcoder.html");
  while (f.getline(buf, N))
    txt += buf, txt += '\n';
  f.close();
  // <time class=\"fixtime-full\">([^<]*)[\\s\\S]*?<a[^>]*>([^<]*)[\\s\\S]*?<td class=\"text-center\">([^<]*)
  // <time class="fixtime-full">([^<]*)[\s\S]*?<a href="([^"]*)">([^<]*)[\s\S]*?<td class="text-center">([^<]*)
  regex base_regex("<time class=\"fixtime-full\">([^<]*)[\\s\\S]*?<a href=\"([^\"]*)\">([^<]*)[\\s\\S]*?<td class=\"text-center\">([^<]*)");
  smatch base_match;
  string::const_iterator it = txt.begin();
  while (regex_search(it, txt.cend(), base_match, base_regex)) {
    // for (int i = 1; i < base_match.size(); i++)
    //   cout << base_match[i].str() << endl;
    Contest ct = {};
    ct.platform = "AtCoder";
    ct.link = "https://atcoder.jp" + string(base_match[2]);
    // 2024-03-16(Sat) 20:00
    stringstream(base_match[1]) >> get_time(&ct.start_time, "%Y-%m-%d(%a) %H:%M");
    ct.start_second = mktime(&ct.start_time);
    // stringstream(base_match[3]) >> get_time(&ct.length, "%H:%M");
    sscanf(string(base_match[4]).c_str(), "%d:%d", &ct.hour, &ct.minute);
    ct.name = base_match[3];
    cts.push_back(ct);
    // strftime(buf, N, "%Y-%m-%d(%a) %H:%M", &ct.start_time);
    // cout << buf << endl;
    // sprintf(buf, "%02d:%02d", ct.hour, ct.minute);
    // cout << buf << endl;
    it = base_match[0].second;
  }
}
void get_luogu_contest() {
  system("D:/Program/anaconda4/python.exe E:/oj_contest_calendar/get_html.py https://www.luogu.com.cn/contest/list E:/oj_contest_calendar/luogu.html");
  string txt;
  ifstream f("luogu.html");
  while (f.getline(buf, N))
    txt += buf, txt += '\n';
  f.close();
  regex base_regex("href=\"(/contest/[0-9]{6})\"[^>]*>[\\s]*(.*)[\\s\\S]*?<time>([^<]*)</time> ~ <time>([^<]*)");
  smatch base_match;
  string::const_iterator it = txt.begin();
  while (regex_search(it, txt.cend(), base_match, base_regex)) {
    // for (int i = 1; i < base_match.size(); i++)
    //   cout << base_match[i].str() << endl;
    Contest ct = {};
    ct.platform = "洛谷";
    ct.link = "https://www.luogu.com.cn" + string(base_match[1]);
    // 2024-03-16(Sat) 20:00
    ct.start_time.tm_year = 2024 - 1900;
    stringstream(base_match[3]) >> get_time(&ct.start_time, "%m-%d %H:%M");
    ct.start_second = mktime(&ct.start_time);
    tm end_time = ct.start_time;
    stringstream(base_match[4]) >> get_time(&end_time, "%H:%M");
    int t = mktime(&end_time) - mktime(&ct.start_time);
    ct.hour = t / 3600, ct.minute = (t % 3600) / 60;
    // sscanf(string(base_match[3]).c_str(), "%d:%d", &ct.hour, &ct.minute);
    ct.name = base_match[2];
    cts.push_back(ct);
    // strftime(buf, N, "%Y-%m-%d(%a) %H:%M", &ct.start_time);
    // cout << buf << endl;
    // sprintf(buf, "%02d:%02d", ct.hour, ct.minute);
    // cout << buf << endl;
    it = base_match[0].second;
  }
}
string f1(tm t) {
  strftime(buf, N, "%Y-%m-%d(%a) %H:%M", &t);
  return buf;
}
string f2(int hour, int minute) {
  sprintf(buf, "%02d:%02d", hour, minute);
  return buf;
}
signed main() {
  system("chcp 65001");
  get_codeforces_contest();
  get_atcoder_contest();
  get_luogu_contest();
  sort(all(cts), [](Contest &a, Contest &b) { return a.start_second < b.start_second || (a.start_second == b.start_second && a.name < b.name); });
  // struct Contest { string platform; string link; tm start_time; int hour, minute; string name; };
  ofstream f("E:/oj_contest_calendar/text.md");
  f << "# <div style=\"text-align:center\">OJ Contest Calendar</div>" << endl;
  // f << "|<div style=\"width:150px;text-align:center\">Start Time</div>|Contest Name|<div style=\"width:75px;text-align:center\">Duration</div>|" << endl;
  // f << "|---|---|---|" << endl;
  f << "<table>" << endl;
  f << "<thead>" << endl;
  f << "<tr>" << endl;
  f << "<th><div style=\"width:150px;text-align:center\">Start Time</div></th>" << endl;
  f << "<th>Contest Name</th>" << endl;
  f << "<th><div style=\"width:75px;text-align:center\">Duration</div></th>" << endl;
  f << "</tr>" << endl;
  f << "</thead>" << endl;
  f << "<tbody>" << endl;
  int now = time(0), day = now / 86400 * 86400;
  for (auto&& [platform, link, start_time, start_second, hour, minute, name] : cts) {
    if (start_second < now)
      continue;
    // strftime(buf, N, "%Y-%m-%d(%a) %H:%M", &start_time);
    // cout << buf << ' ';
    // sprintf(buf, "%02d:%02d", hour, minute);
    // cout << buf << ' ' << name << endl;
    // f << "|<div style=\"width:150px;text-align:center;color:#337AB7;\">" + f1(start_time) + "</div>|" + "<a href=\"" + link + "\" target=\"_blank\">" + name + "</a>" + "|<div style=\"width:75px;text-align:center\">" + f2(hour, minute) + "</div>|" << endl;
    if (day <= start_second && start_second < day + 86400)
      f << "<tr style=\"background-color:#C3E6CB\">" << endl;
    else
      f << "<tr>" << endl;
    f << "<td><div style=""\"width:150px;text-align:center;\">" + f1(start_time) + "</div></td>" << endl;
    f << "<td><a href=\"" + link + "\" target=\"_blank\">" + name + "</a></td>" << endl;
    f << "<td><div style=\"width:75px;text-align:center\">" + f2(hour, minute) + "</div></td>" << endl;
    f << "</tr>" << endl;
  }
  f << "</tbody>" << endl;
  f << "</table>" << endl;
  f << "<div style=\"text-align:center;\">made by " "<a href=\"https://inf-512.github.io/\" target=\"_blank\">INF_512</a>" "</div>" << endl;
  f.close();
  // system("D:/Program/Git/git-bash.exe --cd-to-home -c 'E:/oj_contest_calendar/pushup.bat'");
  return 0;
}

// 有没有把codeforces,atcoder,luogu等主流竞赛平台的比赛时间整合到一起的软件

// OJ比赛日历

// 显示codeforces,atcoder,luogu比赛时间

// 比赛分类，按平台分类，按日期分类，过滤

// 一个比赛包含：日期(星期)，开始时间，持续时间，名称，比赛链接

// 1. 写一个exe生成md文件
// a. md文件内容
// # OJ比赛日历
// （一个表格：列包括开始时间、比赛名称、持续时间）
// 开始时间：日期+星期+时间
// 比赛名称：同名（在点击比赛名称时，以新建窗口的方式，跳转到对应页面）
// 持续时间：同名
// 最后，包含codeforces，atcoder，luogu，可以 made by [INF_512](我的首页)
// 冷门比赛平台，计蒜客，牛客，力扣，acwing，有空再加
// 2. 先删掉垃圾桶，再上传到github
// 3. 每日更新
// 4. 首页更新

// 2. 同一天相同颜色，当天特殊颜色
// 4. 优化超链接显示

