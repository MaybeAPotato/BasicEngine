#ifndef SINGLETON_H
#define SINGLETON_H

namespace Core {
	template <class T>
	class Singleton {
		static T* m_instance;

	protected:
		Singleton() {}
		~Singleton(){
			delete m_instance;
			m_instance = nullptr;
		}
	public:
		static T& GetInstance() {
			if (m_instance != nullptr) {
				return *m_instance;
			}
			else {
				m_instance = new T();
				return *m_instance;
			}
		}
	};
	template <class T>
	T* Singleton<T>::m_instance = nullptr;
}
#endif // !SINGLETON_H