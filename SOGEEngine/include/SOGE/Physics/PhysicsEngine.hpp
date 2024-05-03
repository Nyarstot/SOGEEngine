#ifndef SOGE_PHYSICS_ENGINE_HPP
#define SOGE_PHYSICS_ENGINE_HPP

namespace soge
{
    class PhysicsEngine final
    {
    private:


    protected:
        PhysicsEngine() = default;
        static PhysicsEngine* sInstance;

    public:
        PhysicsEngine(PhysicsEngine&)       = delete;
        void operator = (PhysicsEngine&)    = delete;

        void Update();

    public:
        static PhysicsEngine* GetInstance();

    };
}

#endif // !SOGE_PHYSICS_ENGINE_HPP
