#pragma once
#include <list>
#include <functional>
#include <optional>
template<
	typename HandlerReturnType,
	typename HandlerArgumentType,
	typename HandlerContainerType = std::list<std::function<HandlerReturnType(HandlerArgumentType)>>
>
class Handler : public HandlerContainerType
{
public:

	class AutoRevokeToken
	{
		std::optional<std::remove_reference_t<decltype(Handler{}.end()) >> m_iter{};
		Handler* m_container;
	public:
		AutoRevokeToken() = default;

		AutoRevokeToken(decltype(Handler{}.end()) iter, Handler& handler) : m_iter{ iter }, m_container{&handler }
		{
		}

		AutoRevokeToken(AutoRevokeToken&& rhs) noexcept : m_iter{ std::move(rhs.m_iter) }, m_container{ rhs.m_container }
		{
			rhs.m_iter.reset();
		}

		AutoRevokeToken& operator=(AutoRevokeToken&& rhs) noexcept
		{
			m_iter.swap(rhs.m_iter);
			return *this;
		}

		operator decltype(m_iter)(){ return *m_iter; }

		~AutoRevokeToken()
		{
			if (m_iter)
				m_container.erase(*m_iter);
		}
	};

};

