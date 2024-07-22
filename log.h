#pragma once

#include<memory>
#include<string>
#include<list>
#include<iostream>
#include<fstream>

namespace sylar
{

//��־�¼�
class logEvent {

public:
	logEvent();

	typedef std::shared_ptr<logEvent> event;
private:
	std::string mContent; //��־����
	const char* mFile = nullptr; //�ļ���
	uint32_t mThreadID;  //�߳�ID
	uint32_t mfiberID;   //Э��ID
	uint64_t mTime;      //��־ʱ��

};

//��־�ȼ�
class logLevel
{
public:
	enum level
	{
		DEBUG = 1,
		INFO = 2,
		WARN = 3,
		ERROR = 4,
		FATAL = 5

	};
};




//��־�����
class logAppender
{
public:
	typedef std::shared_ptr<logAppender> appender;

	~logAppender();

	virtual void log(logLevel::level level, logEvent::event e) = 0;
	
protected:
	logLevel::level mLevel;
	logFormat::format mFormat;
};

//��־�� ������־����
class logger
{
public:
	typedef std::shared_ptr<logger> loggerPtr;
	logger(const std::string& name = "root");

	void log(logLevel::level level, logEvent::event event);

	void addAppender(logAppender::appender appender);
	void delAppender(logAppender::appender appender);

	void setLevel(logLevel::level level);
	logLevel::level getLevel();


	
	void debug(logEvent::event e);
	void info(logEvent::event e);
	void warn(logEvent::event e);
	void error(logEvent::event e);
	void fatal(logEvent::event e);

private:
	std::string name;
	logLevel::level mLevel;
	std::list<logAppender::appender> mAppender;
};


class stdoutAppender :public logAppender
{
public:
	typedef std::shared_ptr<stdoutAppender> ptr;
	void log(logLevel::level level,logEvent::event e) override;
};

class fileAppender :public logAppender
{
public:
	typedef std::shared_ptr<fileAppender> ptr;
	void log(logLevel::level level, logEvent::event e) override;

	fileAppender(const std::string& name);

private:
	std::string mfileName;
	std::ofstream mFileStream;
};


//��־��ʽ
class logFormat
{
public:
	typedef std::shared_ptr<logFormat> format;
	std::string format(logEvent::event event);
};


}