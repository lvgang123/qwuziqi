#include "qhelper.h"

bool QHelper::ipLive(const QString &ip, int port, int out)
{
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost(ip, port);
    //超时没有连接上则判断不在线
    return tcpClient.waitForConnected(out);
}

void QHelper::Close_other(const QString str_exe)
{
    QStringList str_PID;
    QProcess process;
    process.start("tasklist.exe", QStringList()<<"-fi"<<QString("imagename eq %1.exe").arg(str_exe)<<"/fo"<<"CSV");

    if(process.waitForFinished())
    {
        QString result = process.readAll();
        for(int i=0;i<result.count();i++)
        {
            if(result.at(i)==str_exe.at(0))
            {
                QString str_judge;
                 for(int j=0;j<str_exe.count();j++)
                 {
                     str_judge+=result.at(i+j);
                 }
                 if(str_judge==str_exe)
                 {
                     QString str_tran;
                     bool start_bool=false;
                     int start_int = 0;
                     for(int k=0;k<(result.count()-i);k++)
                     {
                         if(result.at(i+k)=='"')
                         {
                             start_int++;
                             if(start_int==3)
                             {
                                 break;
                             }
                             if(start_int==2)
                             {
                                 start_bool=true;
                             }
                         }else
                         {
                             if(start_bool)
                             {
                                 str_tran+=result.at(i+k);
                             }
                         }
                     }
                     str_PID<<str_tran;
                 }
            }
        }
    }

    //将当前进程在列表中移除
    for(int i=0;i<str_PID.count();i++)
    {
        QString tran_str=str_PID.at(i);
        if(tran_str.toInt()==getpid())
        {
            str_PID.removeAt(i);
        }
    }

    //删除多余进程
    for(int i=0;i<str_PID.count();i++)
    {
        process.execute("taskkill" , QStringList()<<"-f"<<"-pid"<<str_PID.at(i));
    }
}

void QHelper::runWithSystem(const QString &strName, const QString &strPath, bool autoRun)
{
#ifdef Q_OS_WIN
    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    reg.setValue(strName, autoRun ? strPath : "");
#endif
}

QString QHelper::appName()
{
    //没有必要每次都获取,只有当变量为空时才去获取一次
    static QString name;
    if (name.isEmpty()) {
        name = qApp->applicationFilePath();
        QStringList list = name.split("/");
        name = list.at(list.count() - 1).split(".").at(0);
    }

    return name;
}

QString QHelper::appPath()
{
#ifdef Q_OS_ANDROID
    return QString("/sdcard/Android/%1").arg(appName());
#else
    return qApp->applicationDirPath();
#endif
}

void QHelper::initRand()
{
    //初始化随机数种子
    QTime t = QTime::currentTime();
    qsrand(t.msec() + t.second() * 1000);
}

void QHelper::writ_log(QString str_log ,int line,QString _file)
{
    //获取当前时间
    QTime local(QTime::currentTime());
    int year_current = local.toString("yy").toInt();
    int month_current= local.toString("MM").toInt();
    int day_cuurent = local.toString("dd").toInt();
    int hour_current = local.toString("hh").toInt();
    int minute_current = local.toString("mm").toInt();
    int second_current = local.toString("ss").toInt();

    QString str_write=QString("[%1:%2](%3-%4-%5 %6时%7分%8秒)").arg(_file).arg(line).arg(year_current)
                            .arg(month_current).arg(day_cuurent).arg(hour_current).arg(minute_current)
                            .arg(second_current);
    for(int i=70;i-str_write.count()>=0;){
        str_write+=" ";
    }
    str_log+='\n';
    str_write+=str_log;
    //创建文件对象
    QFile file(QString("%1/log_deal_main.txt").arg(QHelper::appPath()));
    //打开文件
    bool isok=file.open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Append);
    if(isok==true){
        QTextStream out(&file);
        out<<str_write;
    }
    file.close();
}

void QHelper::closeAll()     //关闭程序函数
{
    Delay_MSec(100);
    exit(0);
}

int QHelper::delete_line(QFile* file,int delete_num)
{
    QString line;
    QStringList save_list;

    //读取文件
    bool read_ok=file->open(QIODevice::ReadOnly | QIODevice::Text);
    if(read_ok==true){
        QTextStream out(file);
        int num=0;
        while(!out.atEnd()){
            line = out.readLine();
            if(num>=delete_num)
                save_list<<line;
            num++;
        }
    }else{
        qDebug()<<"读取文件失败";
    }
    file->close();

    //写入文件
    bool isok=file->open(QIODevice::WriteOnly | QIODevice::Text);
    if(isok==true){
        QTextStream out(file);
        for(int i=0;i<save_list.count();i++)
        {
            out << save_list.at(i) << endl;
        }
    }else{
        qDebug()<<"写入文件失败";
    }
    file->close();

    return save_list.count();
}

void QHelper::Delay_MSec(unsigned int msec)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}
