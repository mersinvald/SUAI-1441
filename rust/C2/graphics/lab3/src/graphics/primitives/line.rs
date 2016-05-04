use sdl2::pixels::Color;
use sdl2::render::Renderer;
use sdl2_gfx::primitives::DrawRenderer;

use graphics::primitives::*;
use graphics::math::matrix::*;

pub struct Line {
    p1:      Point2D,
    p2:      Point2D,
    anchor:  Point2D,
    color:   Color
}

#[allow(dead_code)]
impl Line {
    pub fn new(point1: &Point2D, point2: &Point2D, color: Color) -> Line {
        let average = Point2D::new(
            (point2.x + point1.x) / 2.0,
            (point2.y + point1.y) / 2.0,
        );

        Line {
            p1:      point1.clone(),
            p2:      point2.clone(),
            anchor:  average,
            color:   color,
        }
    }

    fn draw_bresenham_line(&self, renderer: &Renderer) {
        use std::mem::swap;

        let mut x1 = self.p1.x as i16;
        let mut y1 = self.p1.y as i16;
        let mut x2 = self.p2.x as i16;
        let mut y2 = self.p2.y as i16;

        let steep = (y2 - y1).abs() > (x2 - x1).abs();
        if steep {
            swap(&mut x1, &mut y1);
            swap(&mut x2, &mut y2);
        }

        if x1 > x2 {
            swap(&mut x1, &mut x2);
            swap(&mut y1, &mut y2);
        }

        let dx =  x2 - x1;
        let dy = (y2 - y1).abs();

        let mut error = dx / 2;
        let mut y = y1;

        let ystep = if y1 < y2 { 1 } else { -1 };

        for x in x1..x2 {
            renderer.pixel(
                if steep { y } else { x },
                if steep { x } else { y },
                self.color
            ).unwrap();

            error -= dy;
            if error < 0 {
                y     += ystep;
                error += dx;
            }
        }
    }


    pub fn draw_builtin_line(&self, renderer: &Renderer) {
        renderer.line(
            self.p1.x as i16,
            self.p1.y as i16,
            self.p2.x as i16,
            self.p2.y as i16,
            self.color
        ).unwrap();
    }
}

impl Primitive2D for Line {
    fn to_matrix(&self) -> Matrix {
        Matrix::new(
            vec![[self.p1.x,      self.p1.y,      1.0],
                 [self.p2.x,      self.p2.y,      1.0]]
        )
    }

    fn from_matrix(&mut self, m: &Matrix) {
        self.p1 = Point2D::new(m.matrix[0][0], m.matrix[0][1]);
        self.p2 = Point2D::new(m.matrix[1][0], m.matrix[1][1]);
    }

    fn anchor_point(&self) -> Point2D {
        self.anchor.clone()
    }

    fn set_anchor_point(&mut self, anchor: &Point2D) {
        self.anchor = anchor.clone();
    }

    #[inline]
    fn draw(&self, renderer: &Renderer) {
        self.draw_bresenham_line(renderer);
    }

    fn fill(&self, renderer: &Renderer) {
        self.draw_bresenham_line(renderer);
    }
}
