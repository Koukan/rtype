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

	for (; nbThread > 0; nbThread--)
	{
		thread = new Net::Thread(this, &ThreadPool::handleTask);
		_threadsList.push_back(thread);
		thread->start();
	}
}

void		ThreadPool::pushTask(Task &task)
{
	Net::ScopedLock		lock(this->_condvar);

	this->_tasksList.push(&task);
}

void		ThreadPool::handleTask()
{
	Task	*task;

	while (true)
	{
		this->_condvar.lock();
		if (this->_tasksList.empty())
			this->_condvar.wait();
		else
		{
			task = this->_tasksList.front();
			this->_tasksList.pop();
			this->_condvar.unlock();
			(*task)();
			delete task;
		}
	}
}
