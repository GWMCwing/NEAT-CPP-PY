#ifndef __NEAT_ACTIVATION_HPP__
#define __NEAT_ACTIVATION_HPP__

#include <vector>
#include <math.h>
#include "./Helper.hpp"

namespace NEAT {

    // forward declaration
    template <typename dType>
    struct ActivationFunction_Factory;

    // Base class for all activation functions
    template <typename dType = double>
    struct ActivationFunction {
        virtual ~ActivationFunction() = default;
    };

    /**
     * @brief Abstract class for all single input activation functions
     *
     * @tparam dType data type of the input and output
     */
    template <typename dType = double>
    struct ActivationFunction_Single : public ActivationFunction<dType> {
    public:
        virtual dType operator()(dType) = 0;
        virtual ~ActivationFunction_Single() = default;
    };

    /**
     * @brief Abstract class for all multiple input activation functions
     *
     * @tparam dType data type of the input and output
     */
    template <typename dType = double>
    struct ActivationFunction_Multiple : public ActivationFunction<dType> {
    public:
        // TODO: parameter may change
        virtual std::vector<dType> operator()(std::vector<dType>) = 0;
    };

    template <typename dType = double>
    struct Sigmoid final : public ActivationFunction_Single<dType> {
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

    template <typename dType = double>
    struct Tanh final : public ActivationFunction_Single<dType> {
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

    template <typename dType = double>
    struct ReLU final : public ActivationFunction_Single<dType> {
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

    template <typename dType = double>
    struct Step final : public ActivationFunction_Single<dType> {
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

    template <typename dType = double>
    struct Identity final : public ActivationFunction_Single<dType> {
        dType operator()(dType x) override {
            return x;
        }
    private:
        template <typename dType2>
        friend ActivationFunction_Factory<dType2>* getActivationFunction_Factory();
        Identity() = default;
        Identity(const Identity&) = delete;
        Identity& operator=(const Identity&) = delete;
    };

    /**
     * @brief Factory class for all activation functions
     *
     * @tparam dType data type of the input and output
     */

    template <typename dType = double>
    class ActivationFunction_Factory final {
    public:
        Sigmoid<dType>* sigmoid = nullptr;
        Tanh<dType>* tanh = nullptr;
        ReLU<dType>* reLU = nullptr;
        Step<dType>* step = nullptr;
        Identity<dType>* identity = nullptr;
        bool init = false;

        ActivationFunction<dType>* getRandomActivationFunction_single() const {
            return functions_single[uniformIntDistribution(0, static_cast<int>(functions_single.size() - 1))];
        }

        ActivationFunction<dType>* getRandomActivationFunction_Multiple() const {
            if (functions_multiple.size() == 0) return nullptr;
            return functions_multiple[uniformIntDistribution(0, static_cast<int>(functions_multiple.size() - 1))];
        }

        ActivationFunction<dType>* getRandomActivationFunction() const {
            return functions[uniformIntDistribution(0, static_cast<int>(functions.size() - 1))];
        }

        ~ActivationFunction_Factory() {
            delete sigmoid;
            delete tanh;
            delete reLU;
            delete step;
            delete identity;
        }
    private:
        const std::vector<ActivationFunction_Single<dType>*> functions_single =
        { sigmoid, tanh, reLU, step, identity };
        const std::vector<ActivationFunction_Multiple<dType>*> functions_multiple =
        {};
        std::vector<ActivationFunction<dType>*> functions = {};
        ActivationFunction_Factory() {
            functions.insert(functions.end(), functions_single.begin(), functions_single.end());
            functions.insert(functions.end(), functions_multiple.begin(), functions_multiple.end());
        }
        template <typename dType2>
        friend ActivationFunction_Factory<dType2>* getActivationFunction_Factory();
        ActivationFunction_Factory(const ActivationFunction_Factory&) = delete;
        ActivationFunction_Factory& operator=(const ActivationFunction_Factory&) = delete;
    };

    /**
     * @brief Get the ActivationFunction Factory object, Singleton pattern
     *
     * @tparam dType data type of the input and output
     * @return ActivationFunction_Factory<dType>* pointer to the factory
     */
    template <typename dType = double>
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
