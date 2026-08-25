import std;

using std::shared_ptr;

enum class Topic: char {
    NO_HELP_TOPIC = 0,
    PRINT_TOPIC = 1,
    PAPER_ORIENTATION = 2,
    APPLICATION_TOPIC = 3,
    PAPER_ORIENTATION_TOPIC = 4,
    // more topics
};

// Abstract handler
// defines an interface for handling requests.
class HelpHandler {
private:
    HelpHandler* successor;
    Topic topic;
public:
    explicit HelpHandler(HelpHandler* h = nullptr, Topic t = Topic::NO_HELP_TOPIC):
        successor{h}, topic{t} {}

    [[nodiscard]]
    virtual bool hasHelp() const noexcept {
        return topic != Topic::NO_HELP_TOPIC;
    }

    virtual void setHandler(HelpHandler* h, Topic t) {
        successor = h;
        topic = t;
    }

    virtual void handleHelp() const {
        std::println("HelpHandler::handleHelp called");
        // (optional) implements the successor link.
        if (successor) {
            successor->handleHelp();
        }
    }

    virtual ~HelpHandler() = default;

    HelpHandler(const HelpHandler&) = delete;
    HelpHandler& operator=(const HelpHandler&) = delete;
};


class Widget: public HelpHandler {
private:
    Widget* parent;
protected:
    explicit Widget(Widget* w, Topic t = Topic::NO_HELP_TOPIC):
        HelpHandler(w, t), parent{w} {
        parent = w;
    }
public:
    Widget(const Widget&) = delete;
    Widget& operator=(const Widget&) = delete;
};

// Concrete handler
// handles requests it is responsible for.
class Button: public Widget {
public:
    explicit Button(shared_ptr<Widget> h, Topic t = Topic::NO_HELP_TOPIC):
        Widget(h.get(), t) {}

    void handleHelp() const override {
        // If the Concrete handler can handle the request, it does so.
        // Otherwise, it forwards the request to its successor.
        std::println("Button::handleHelp called");
        if (hasHelp()) {
            // handles requests it is responsible for.
        } else {
            // can access its successor.
            HelpHandler::handleHelp();
        }
    }
};

// Concrete handler
class Dialog: public Widget {
public:
    explicit Dialog(shared_ptr<HelpHandler> h, Topic t = Topic::NO_HELP_TOPIC):
        Widget(nullptr) {
        setHandler(h.get(), t);
    }

    void handleHelp() const override {
        std::println("Dialog::handleHelp called");
        // Widget operations that Dialog overrides...
        if(hasHelp()) {
            // offer help on the dialog
        } else {
            HelpHandler::handleHelp();
        }
    }
};

class Application: public HelpHandler {
public:
    explicit Application(Topic t):
        HelpHandler(nullptr, t) {}

    void handleHelp() const override {
        std::println("Application::handleHelp called");
        // show a list of help topics
    }
};

int main(int argc, char* argv[]) {
    shared_ptr<Application> application = std::make_shared<Application>(Topic::APPLICATION_TOPIC);
    shared_ptr<Dialog> dialog = std::make_shared<Dialog>(application, Topic::PRINT_TOPIC);
    shared_ptr<Button> button = std::make_shared<Button>(dialog, Topic::PAPER_ORIENTATION_TOPIC);

    button->handleHelp();
    return 0;
}