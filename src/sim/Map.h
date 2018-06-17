#pragma once

#include <QOpenGLBuffer> 
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram> 
#include <QOpenGLTexture> 
#include <QOpenGLVertexArrayObject> 
#include <QOpenGLWidget>
#include <QVector>

#include "Maze.h"
#include "MazeView.h"
#include "MouseGraphic.h"
#include "TriangleGraphic.h"

namespace mms {

class Map : public QOpenGLWidget, protected QOpenGLFunctions {
    
    // NOTE: Inheriting from QOpenGLFunctions allows
    // us to call the OpenGL functions directly

    Q_OBJECT

public:

    Map(QWidget* parent = 0);

    void setMaze(const Maze* maze);
    void setView(const MazeView* view);
    void setMouseGraphic(const MouseGraphic* mouseGraphic);

    // Retrieves OpenGL version info
    QVector<QString> getOpenGLVersionInfo();

    void shutdown();

protected:

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:

    // Logger of OpenGL warnings and errors
    QOpenGLDebugLogger m_openGLLogger;
    void initOpenGLLogger();

    // No ownership here - only pointers
    const Maze* m_maze;
    const MazeView* m_view;
    const MouseGraphic* m_mouseGraphic;

    // The map's window size, in pixels
    int m_windowWidth;
    int m_windowHeight;

    // Polygon program variables
    QOpenGLShaderProgram m_polygonProgram;
    QOpenGLVertexArrayObject m_polygonVAO;
    QOpenGLBuffer m_polygonVBO;

    // Texture program variables
    QOpenGLTexture* m_textureAtlas;
    QOpenGLShaderProgram m_textureProgram;
    QOpenGLVertexArrayObject m_textureVAO;
    QOpenGLBuffer m_textureVBO;

    // Initialize the graphics
    void initPolygonProgram();
    void initTextureProgram();

    // Drawing helper methods
    void repopulateVertexBufferObjects(
        const QVector<TriangleGraphic>& mouseBuffer);
    void drawMap(
        const Coordinate& currentMouseTranslation,
        const Angle& currentMouseRotation,
        QOpenGLShaderProgram* program,
        QOpenGLVertexArrayObject* vao,
        int vboStartingIndex,
        int count);
};

} // namespace mms
