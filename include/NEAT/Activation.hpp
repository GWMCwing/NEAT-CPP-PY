#ifndef __NEAT_ACTIVATION_HPP__
#define __NEAT_ACTIVATION_HPP__

#include <vector>
#include <math.h>

namespace NEAT {

    // forward declaration
    template <typename dType>
    struct ActivationFunction_Factory;

    // Base class for all activation functions
    template <typename dType = float>
    struct ActivationFunction { };

    /**
     * @brief Abstract class for all single input activation functions
     *
     * @tparam dType data type of the input and output
     */
    template <typename dType = float>
    struct ActivationFunction_Single : public ActivationFunction<dType> {
    public:
        virtual dType operator()(dType) = 0;
    };

    /**
     * @brief Abstract class for all multiple input activation functions
     *
     * @tparam dType data type of the input and output
     */
    template <typename dType = float>
    struct ActivationFunction_Multiple : public ActivationFunction<dType> {
    public:
        // TODO: parameter may change
        virtual std::vector<dType> operator()(std::vector<dType>) = 0;
    };

    template <typename dType = float>
    struct Sigmoid : public ActivationFunction_Single<dType> {
        dType operator()(dType x) override {
            return 1 / (1 + exp(-x));
        }
    private:
        template <typename dType2>
        friend ActivationFunction_Factory<dType2>* getActivationFunction_Factory();
        Sigmoid() = default;
        Sigmoid(const Sigmoid&) = delete;
        Sigmoid& operator=(const Sigmoid&) = delete;
    };

    template <typename dType = float>
    struct Tanh : public ActivationFunction_Single<dType> {
        dType operator()(dType x) override {
            return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
        }
    private:
        template <typename dType2>
        friend ActivationFunction_Factory<dType2>* getActivationFunction_Factory();
        Tanh() = default;
        Tanh(const Tanh&) = delete;
        Tanh& operator=(const Tanh&) = delete;

    };

    template <typename dType = float>
    struct ReLU : public ActivationFunction_Single<dType> {
        dType operator()(dType x) override {
            return x > 0 ? x : 0;
        }
    private:
        template <typename dType2>
        friend ActivationFunction_Factory<dType2>* getActivationFunction_Factory();
        ReLU() = default;
        ReLU(const ReLU&) = delete;
        ReLU& operator=(const ReLU&) = delete;
    };

    template <typename dType = float>
    struct Step : public ActivationFunction_Single<dType> {
        dType operator()(dType x) override {
            return x > 0 ? 1 : 0;
        }
    private:
        template <typename dType2>
        friend ActivationFunction_Factory<dType2>* getActivationFunction_Factory();
        Step() = default;
        Step(const Step&) = delete;
        Step& operator=(const Step&) = delete;
    };

    template <typename dType = float>
    struct Identity : public ActivationFunction_Single<dType> {
        dType operator()(dType x) override {
            return x;
        }
        template <typename dType2>
        friend ActivationFunction_Factory<dType2>* getActivationFunction_Factory();
    private:
        Identity() = default;
        Identity(const Identity&) = delete;
        Identity& operator=(const Identity&) = delete;
    };

    /**
     * @brief Factory class for all activation functions
     *
     * @tparam dType data type of the input and output
     */

    template <typename dType = float>
    struct ActivationFunction_Factory {
        Sigmoid<dType>* sigmoid = nullptr;
        Tanh<dType>* tanh = nullptr;
        ReLU<dType>* reLU = nullptr;
        Step<dType>* step = nullptr;
        Identity<dType>* identity = nullptr;
        bool init = false;
    };

    /**
     * @brief Get the ActivationFunction Factory object, Singleton pattern
     *
     * @tparam dType data type of the input and output
     * @return ActivationFunction_Factory<dType>* pointer to the factory
     */
    template <typename dType = float>
    ActivationFunction_Factory<dType>* getActivationFunction_Factory() {
        static ActivationFunction_Factory<dType> factory;
        if (factory.init) return &factory;
        factory.sigmoid = new Sigmoid<dType>();
        factory.tanh = new Tanh<dType>();
        factory.reLU = new ReLU<dType>();
        factory.step = new Step<dType>();
        factory.identity = new Identity<dType>();
        factory.init = true;
        return &factory;
    }
}

#endif // __NEAT_ACTIVATION_HPP__
