#include "log.h"

namespace sylar
{
	logger::logger(const std::string& name)
	{
	}
	void logger::log(logLevel::level level, logEvent::event event)
	{
		if (level >= mLevel)
		{
			for (auto appender : mAppender)
			{
				appender->log(level, event);
			}
		}
	}
	void logger::addAppender(logAppender::appender appender)
	{
		mAppender.push_back(appender);
	}

	void logger::delAppender(logAppender::appender appender)
	{
		for (auto iter = mAppender.begin(); iter != mAppender.end(); iter++)
		{
			if (*iter == appender)
			{
				mAppender.erase(iter);
			}
		}
	}

	void logger::setLevel(logLevel::level level)
	{
		mLevel = level;
	}
	
	logLevel::level logger::getLevel()
	{
		return mLevel;
	}

	void logger::debug(logEvent::event e)
	{
		log(logLevel::DEBUG, e);
	}

	void logger::info(logEvent::event e)
	{
		log(logLevel::INFO, e);

	}

	void logger::warn(logEvent::event e)
	{
		log(logLevel::WARN, e);

	}

	void logger::error(logEvent::event e)
	{
		log(logLevel::ERROR, e);

	}

	void logger::fatal(logEvent::event e)
	{
		log(logLevel::FATAL, e);

	}

	void stdoutAppender::log(logLevel::level level, logEvent::event e)
	{
		if (level >= mLevel)
		{
			std::cout << level << e;
		}
	}

	void fileAppender::log(logLevel::level level, logEvent::event e)
	{
		if (level >= mLevel)
		{
			std::cout << mFormat();
		}
	}

	fileAppender::fileAppender(const std::string& name)
	{
	}

}


