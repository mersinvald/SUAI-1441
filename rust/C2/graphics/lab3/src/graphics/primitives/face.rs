use sdl2::pixels::Color;
use sdl2::render::Renderer;
use sdl2_gfx::primitives::DrawRenderer;

use graphics::primitives::*;
use graphics::primitives::line::*;
use graphics::math::matrix::*;

pub struct Face {
    a: Point2D,
    b: Point2D,
    c: Point2D,
    anchor: Point2D,
    color: Color,
}

impl Face {
    pub fn new(a: &Point2D, b: &Point2D, c: &Point2D, color: Color) -> Face {
        let average = Point2D::new (
            (a.x + b.x + c.x) / 3.0,
            (a.y + b.y + c.y) / 3.0
        );

        Face {
            a:      a.clone(),
            b:      b.clone(),
            c:      c.clone(),
            anchor: average,
            color:  color
        }
    }

    pub fn new_with_anchor(a: &Point2D, b: &Point2D, c: &Point2D,
                           anchor: &Point2D, color: Color) -> Face {
        Face {
            a:      a.clone(),
            b:      b.clone(),
            c:      c.clone(),
            anchor: anchor.clone(),
            color:  color
        }
    }
}

impl Primitive2D for Face {
    fn to_matrix(&self) -> Matrix {
        Matrix::new(
            vec![[self.a.x, self.a.y, 1.0],
                 [self.b.x, self.b.y, 1.0],
                 [self.c.x, self.c.y, 1.0]]
        )
    }

    fn from_matrix(&mut self, m: &Matrix) {
        self.a = Point2D::new(m.matrix[0][0], m.matrix[0][1]);
        self.b = Point2D::new(m.matrix[1][0], m.matrix[1][1]);
        self.c = Point2D::new(m.matrix[2][0], m.matrix[2][1]);
    }

    fn anchor_point(&self) -> Point2D {
        Point2D::new(self.anchor.x, self.anchor.y)
    }

    fn set_anchor_point(&mut self, anchor: &Point2D) {
        self.anchor = anchor.clone();
    }

    fn draw(&self, renderer: &Renderer) {
        let line_ab = Line::new(&self.a, &self.b, self.color);
        let line_bc = Line::new(&self.b, &self.c, self.color);
        let line_ca = Line::new(&self.c, &self.a, self.color);

        line_ab.draw(renderer);
        line_bc.draw(renderer);
        line_ca.draw(renderer);
    }

    fn fill(&self, renderer: &Renderer) {

    }
}
