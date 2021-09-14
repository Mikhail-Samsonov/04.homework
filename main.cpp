#include <iostream>
#include "src/application.h"

int main() {
    Application app;
    const std::unique_ptr<Document> &doc1 = app.createDocument();
    const std::unique_ptr<Document> &doc2 = app.createDocument();
    const std::unique_ptr<Document> &doc3 = app.importDocument();

    const std::unique_ptr<IShape> &shape1 = doc1->add_line();
    const std::unique_ptr<IShape> &shape2 = doc1->add_circle();
    const std::unique_ptr<IShape> &shape3 = doc1->add_square();
    const std::unique_ptr<IShape> &shape4 = doc2->add_circle();
    const std::unique_ptr<IShape> &shape5 = doc3->add_square();

    doc1->set_color(Color::yellow);
    doc2->set_color(Color::green);
    doc2->set_zoom(50);

    doc1->remove_shape(shape2);

    DefaultDisplay display;
    doc1->draw(display);

    app.exportDocument(doc1);
    return 0;
}
