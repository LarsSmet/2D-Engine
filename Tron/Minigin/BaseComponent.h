#pragma once
//#include "GameObject.h"

	namespace dae
	{

		class GameObject;

		class BaseComponent //acts like monobehaviour in unity
		{
		public:

			BaseComponent(GameObject* go);
			virtual void Update(float deltaTime);
			virtual ~BaseComponent();




		private:



		protected:
			GameObject* m_Owner;
			

		};


	}
