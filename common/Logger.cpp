#include <map>
#include <string>
#include "Logger.hpp"

Logger Logger::logger;

Logger::Log::Log(std::map<PacketType::ContactState::State, std::string> const &states,
		 std::map<PacketType::Call::Call, std::string> const &calls) :
  _states(states), _calls(calls), _end(false)
{
}

Logger::Log &Logger::Log::operator<<(PacketType::ContactState::State state)
{
  using namespace PacketType;

  std::map<ContactState::State, std::string>::const_iterator it = _states.find(state);

  if (it != _states.end())
    std::cout << it->second;
  return (*this);
}

Logger::Log &Logger::Log::operator<<(PacketType::Call::Call type)
{
  using namespace PacketType;

  std::map<Call::Call, std::string>::const_iterator it = _calls.find(type);

  if (it != _calls.end())
    std::cout << it->second;
  return (*this);
}

Logger::Logger()
{
  using namespace PacketType;

  _states[ContactState::Connected] = "connected";
  _states[ContactState::Disconnected] = "disconnected";
  _states[ContactState::Busy] = "busy";
  _states[ContactState::Idle] = "idle";

  _calls[Call::Request] = "requestCall";
  _calls[Call::Accept] = "acceptCall";
  _calls[Call::Reject] = "rejectCall";
  _calls[Call::Hangup] = "hangupCall";
  _calls[Call::Suspend] = "suspendCall";
  _calls[Call::Resume] = "resumeCall";
}
