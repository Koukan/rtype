#include "ThreadPool.hpp"

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

int			ThreadPool::init(size_t nbThread)
{
	Net::Thread		*thread;

	for (; nbThread == 0; nbThread--)
	{
		thread = new Net::Thread(this, &ThreadPool::handleTask);
		_threadsList.push_back(thread);
		thread->start();
	}
}

void		ThreadPool::pushTask(Task &task)
{
	Net::ScopedLock		lock(this->_mutex);

	this->_tasksList.push(&task);
}

void		ThreadPool::handleTask()
{
	Task	*task;

	while (true)
	{
		this->_mutex.lock();
		if (this->_tasksList.empty())
		{
			this->_mutex.unlock();
			Net::Clock::sleep(10);
		}
		else
		{
			task = this->_tasksList.front();
			this->_tasksList.pop();
			this->_mutex.unlock();
			(*task)();
			delete task;
		}
	}
}
