#include "SDL2_gfxPrimitives.h"
#include "application_ui.h"
#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <vector>

using namespace std;

#define EPSILON 0.0001f

struct Coords {
  int x, y;

  bool operator==(const Coords &other) const {
    return x == other.x and y == other.y;
  }
};
struct Polygone {
  std::vector<Coords> points;
};
struct Segment {
  Coords p1, p2;
};

struct Triangle {
  Coords p1, p2, p3;
  bool complet = false;
};

struct Vertex {
  Coords point;
  double angle;

  bool operator<(const Vertex &other) const { return angle < other.angle; }
};

struct Application {
  int width, height;
  Coords focus{100, 100};

  std::vector<Polygone> polygones;
  std::vector<Coords> points;
  std::vector<Triangle> triangles;
  std::vector<Segment> voronoiSeg;
};

// changement => trie par x
bool compareCoords(Coords point1, Coords point2) {
  // Si les points x sont égaux, alors on les distingue selon leur point y
  if (point1.x == point2.x)
    return point1.y < point2.y;

  return point1.x < point2.x;
}

// changement => trie par x
bool compareCoordsReverse(Coords point1, Coords point2) {
  // Si les points x sont égaux, alors on les distingue selon leur point y
  if (point1.x == point2.x)
    return point1.y < point2.y;

  return point1.x > point2.x;
}

/*
   Détermine si un point se trouve dans un cercle définit par trois points
   Retourne, par les paramètres, le centre et le rayon
*/
bool CircumCircle(float pX, float pY, float x1, float y1, float x2, float y2,
                  float x3, float y3, float *xc, float *yc, float *rsqr) {
  float m1, m2, mx1, mx2, my1, my2;
  float dx, dy, drsqr;
  float fabsy1y2 = fabs(y1 - y2);
  float fabsy2y3 = fabs(y2 - y3);

  /* Check for coincident points */
  if (fabsy1y2 < EPSILON && fabsy2y3 < EPSILON)
    return (false);

  if (fabsy1y2 < EPSILON) {
    m2 = -(x3 - x2) / (y3 - y2);
    mx2 = (x2 + x3) / 2.0;
    my2 = (y2 + y3) / 2.0;
    *xc = (x2 + x1) / 2.0;
    *yc = m2 * (*xc - mx2) + my2;
  } else if (fabsy2y3 < EPSILON) {
    m1 = -(x2 - x1) / (y2 - y1);
    mx1 = (x1 + x2) / 2.0;
    my1 = (y1 + y2) / 2.0;
    *xc = (x3 + x2) / 2.0;
    *yc = m1 * (*xc - mx1) + my1;
  } else {
    m1 = -(x2 - x1) / (y2 - y1);
    m2 = -(x3 - x2) / (y3 - y2);
    mx1 = (x1 + x2) / 2.0;
    mx2 = (x2 + x3) / 2.0;
    my1 = (y1 + y2) / 2.0;
    my2 = (y2 + y3) / 2.0;
    *xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
    if (fabsy1y2 > fabsy2y3) {
      *yc = m1 * (*xc - mx1) + my1;
    } else {
      *yc = m2 * (*xc - mx2) + my2;
    }
  }

  dx = x2 - *xc;
  dy = y2 - *yc;
  *rsqr = dx * dx + dy * dy;

  dx = pX - *xc;
  dy = pY - *yc;
  drsqr = dx * dx + dy * dy;

  return ((drsqr - *rsqr) <= EPSILON ? true : false);
}

void drawPoints(SDL_Renderer *renderer, const std::vector<Coords> &points) {
  for (std::size_t i = 0; i < points.size(); i++) {
    filledCircleRGBA(renderer, points[i].x, points[i].y, 3, 240, 240, 23,
                     SDL_ALPHA_OPAQUE);
  }
}

void drawSegments(SDL_Renderer *renderer,
                  const std::vector<Segment> &segments) {
  for (std::size_t i = 0; i < segments.size(); i++) {
    lineRGBA(renderer, segments[i].p1.x, segments[i].p1.y, segments[i].p2.x,
             segments[i].p2.y, 240, 240, 20, SDL_ALPHA_OPAQUE);
  }
}

void drawTriangles(SDL_Renderer *renderer,
                   const std::vector<Triangle> &triangles) {
  for (std::size_t i = 0; i < triangles.size(); i++) {
    const Triangle &t = triangles[i];
    trigonRGBA(renderer, t.p1.x, t.p1.y, t.p2.x, t.p2.y, t.p3.x, t.p3.y, 0, 240,
               160, SDL_ALPHA_OPAQUE);
  }
}

void drawCircles(SDL_Renderer *renderer,
                 const std::vector<Triangle> &triangles) {
  float xC, yC, rC;
  for (std::size_t i = 0; i < triangles.size(); i++) {
    const Triangle &t = triangles[i];
    CircumCircle(t.p1.x, t.p1.y, t.p1.x, t.p1.y, t.p2.x, t.p2.y, t.p3.x, t.p3.y,
                 &xC, &yC, &rC);
    circleRGBA(renderer, xC, yC, sqrt(rC), 30, 30, 30, SDL_ALPHA_OPAQUE);
  }
}

void drawCenterCircles(SDL_Renderer *renderer,
                       const std::vector<Triangle> &triangles) {
  float xC, yC, rC;
  for (std::size_t i = 0; i < triangles.size(); i++) {
    const Triangle &t = triangles[i];
    CircumCircle(t.p1.x, t.p1.y, t.p1.x, t.p1.y, t.p2.x, t.p2.y, t.p3.x, t.p3.y,
                 &xC, &yC, &rC);
    filledCircleRGBA(renderer, xC, yC, 3, 240, 23, 23, SDL_ALPHA_OPAQUE);
  }
}

void drawPolygones(SDL_Renderer *renderer,
                   const std::vector<Polygone> &polygones) {
  for (auto polygone : polygones) {
    std::vector<Coords> points = polygone.points;
    std::vector<Sint16> vx;
    std::vector<Sint16> vy;
    for (auto point : points) {
      vx.push_back(point.x);
      vy.push_back(point.y);
    }
  }
}

/* ********** D  R  A  W  ********** */

void drawVoronoi(Application &app) {

  float xCircle1, yCircle1, rCircle1, xCircle2, yCircle2, rCircle2;
  for (auto _triangle1 : app.triangles) {
    for (auto _triangle2 : app.triangles) {

      int _nb = 0;
      if (_triangle1.p1 == _triangle2.p1 || _triangle1.p1 == _triangle2.p2 ||
          _triangle1.p1 == _triangle2.p3) {
        _nb++;
      }
      if (_triangle1.p2 == _triangle2.p1 || _triangle1.p2 == _triangle2.p2 ||
          _triangle1.p2 == _triangle2.p3) {
        _nb++;
      }
      if (_triangle1.p3 == _triangle2.p1 || _triangle1.p3 == _triangle2.p2 ||
          _triangle1.p3 == _triangle2.p3) {
        _nb++;
      }

      if (_nb == 2) {
        CircumCircle(_triangle1.p1.x, _triangle1.p1.y, _triangle2.p1.x,
                     _triangle2.p1.y, _triangle2.p2.x, _triangle2.p2.y,
                     _triangle2.p3.x, _triangle2.p3.y, &xCircle1, &yCircle1,
                     &rCircle1);
        CircumCircle(_triangle2.p1.x, _triangle2.p1.y, _triangle1.p1.x,
                     _triangle1.p1.y, _triangle1.p2.x, _triangle1.p2.y,
                     _triangle1.p3.x, _triangle1.p3.y, &xCircle2, &yCircle2,
                     &rCircle2);

        Segment _segment = Segment{Coords{(int)xCircle1, (int)yCircle1},
                                   Coords{(int)xCircle2, (int)yCircle2}};

        bool seg = false;

        for (auto _s : app.voronoiSeg) {
          if (seg)
            break;
          seg = _segment.p1 == _s.p1 && _segment.p2 == _s.p2;
        }
        if (!seg)
          app.voronoiSeg.push_back(_segment);
      }
    }
  }
}

void draw(SDL_Renderer *renderer, Application &app) {
  /* Remplissez cette fonction pour faire l'affichage du jeu */
  int width, height;
  SDL_GetRendererOutputSize(renderer, &width, &height);

  drawPolygones(renderer, app.polygones);
  drawTriangles(renderer, app.triangles);
  drawPoints(renderer, app.points);
  drawSegments(renderer, app.voronoiSeg);
  drawVoronoi(app);
}

void construitVoronoi(Application &app) {
  //* --- Trier les points selon x ---*/
  std::sort(app.points.begin(), app.points.end(), compareCoords);

  printf("\n\nAfter sorting vector : ");
  for (auto i = app.points.begin(); i < app.points.end(); i++) {
    cout << "\n(" << i->x << ";" << i->y << ")" << endl;
  }

  //* --- Vider la liste existante de triangles ---*/
  app.triangles.clear();
  app.voronoiSeg.clear();
  app.polygones.clear();

  //* --- Créer un très grand triangle ---*/
  Triangle big =
      Triangle({Coords{-1000, -1000}, Coords{500, 3000}, Coords{1500, -1000}});
  // Le rajouter à la liste de triangles déjà créés
  app.triangles.push_back(big);

  //* --- pour chaque point P du repère --- */
  for (auto point : app.points) {
    // Créer une liste de segments LS
    std::vector<Segment> segments;

    //* --- chaque triangle T déjà créé --- */
    for (std::size_t t = 0; t < app.triangles.size(); t++) {
      Triangle _triangle = app.triangles[t];

      // si le cercle circonscrit contient le point P alors
      float xCircle, yCircle, rCircle;
      if (CircumCircle(point.x, point.y, _triangle.p1.x, _triangle.p1.y,
                       _triangle.p2.x, _triangle.p2.y, _triangle.p3.x,
                       _triangle.p3.y, &xCircle, &yCircle, &rCircle)) {
        // Récupérer les différents segments de ce triangles dans LS
        segments.push_back(Segment{_triangle.p1, _triangle.p2});
        segments.push_back(Segment{_triangle.p2, _triangle.p3});
        segments.push_back(Segment{_triangle.p3, _triangle.p1});

        // Effacer le triangle de la liste
        app.triangles.erase(app.triangles.begin() + t);
        t--;
      }
    }
    //* --- pour chaque segment S de la liste LS faire --- */
    for (std::size_t j = 0; j < segments.size(); j++) {
      Segment _segment1 = segments[j];

      for (std::size_t k = 0; k < segments.size(); k++) {
        Segment _segment2 = segments[k];
        // si un segment est un doublon d’un autre* alors
        if (k != j && _segment1.p1 == _segment2.p2 &&
            _segment1.p2 == _segment2.p1) {
          // On les enlève de la liste
          segments.erase(segments.begin() + k);
          segments.erase(segments.begin() + j);
          j--;
          break;
        }
      }
    }
    //* --- pour Pour chaque segment S de la liste LS faire --- */
    for (auto segment : segments) {
      // créer un nouveau triangle composé du segment S et du point P
      app.triangles.push_back(Triangle({segment.p1, segment.p2, point}));
    }
  }
}

bool handleEvent(Application &app) {
  /* Remplissez cette fonction pour gérer les inputs utilisateurs */
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT)
      return false;
    else if (e.type == SDL_WINDOWEVENT_RESIZED) {
      app.width = e.window.data1;
      app.height = e.window.data1;
    } else if (e.type == SDL_MOUSEWHEEL) {
    } else if (e.type == SDL_MOUSEBUTTONUP) {
      if (e.button.button == SDL_BUTTON_RIGHT) {
        app.focus.x = e.button.x;
        app.focus.y = e.button.y;
        app.points.clear();
      } else if (e.button.button == SDL_BUTTON_LEFT) {
        app.focus.y = 0;
        // Création de points
        app.points.push_back(Coords{e.button.x, e.button.y});
        construitVoronoi(app);
      }
    }
  }
  return true;
}

int main(int argc, char **argv) {
  SDL_Window *gWindow;
  SDL_Renderer *renderer;
  Application app{720, 720, Coords{0, 0}};
  bool is_running = true;

  // Creation de la fenetre
  gWindow = init("Awesome Voronoi", 720, 720);

  if (!gWindow) {
    SDL_Log("Failed to initialize!\n");
    exit(1);
  }

  renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

  /* **********  G A M E   L O O P ********** */
  while (true) {
    // INPUTS
    is_running = handleEvent(app);
    if (!is_running)
      break;

    // EFFACAGE FRAME
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // DESSIN
    draw(renderer, app);

    // VALIDATION FRAME
    SDL_RenderPresent(renderer);

    // PAUSE en ms
    SDL_Delay(1000 / 30);
  }

  // Free resources and close SDL
  close(gWindow, renderer);

  return 0;
}