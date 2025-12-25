#pragma once


class Task {
public:
    virtual ~Task() = default;
    virtual void execute() = 0;
    virtual std::string getId() const = 0;
};

/**
* Count math problems
*/
class MathTask final: public Task {
public:
    MathTask();
    void execute() override;
    [[nodiscard]] std::string getId() const override;
};

/**
* Plot graph
*/
class VisualizationTask final: public Task {
public:
    VisualizationTask();
    void execute() override;
    [[nodiscard]] std::string getId() const override;
};