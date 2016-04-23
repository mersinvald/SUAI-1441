use sdl2;
use sdl2::pixels::Color;
use primitives::*;
use matrix::*;

pub struct Line {
    p1:      Point2D,
    p2:      Point2D,
    average: Point2D,
    color:   Color
}

impl Line {
    pub fn new(x1: f32, y1: f32, x2: f32, y2: f32, color: Color) -> Line {
        Line {
            p1: Point2D {x: x1, y: y1},
            p2: Point2D {x: x2, y: y2},
            average: Point2D {
                x: (x1 + x2)/ 2.0,
                y: (y1 + y2) / 2.0,
            },
            color: color,
        }
    }

    #[allow(dead_code)]
    pub fn from_points(point1: Point2D, point2: Point2D, color: Color) -> Line {
        Line {
            p1: Point2D {x: point1.x, y: point2.y},
            p2: Point2D {x: point2.x, y: point2.y},
            average: Point2D {
                x: (point2.x + point1.x) / 2.0,
                y: (point2.y + point2.y) / 2.0,
            },
            color: color,
        }
    }

    fn draw_bresenham_line<F>(&self, mut set_pixel: F)
        where F: FnMut(i32, i32, Color) {
        use std::mem::swap;

        let mut x1 = self.p1.x as i32;
        let mut y1 = self.p1.y as i32;
        let mut x2 = self.p2.x as i32;
        let mut y2 = self.p2.y as i32;

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
            set_pixel(
                if steep { y } else { x },
                if steep { x } else { y },
                self.color
            );

            error -= dy;
            if error < 0 {
                y     += ystep;
                error += dx;
            }
        }
    }


    pub fn draw_builtin_line(&self, renderer: &mut sdl2::render::Renderer) {
        use sdl2::rect::Point;
        let last = renderer.draw_color();
        renderer.set_draw_color(self.color);
        renderer.draw_line(
            Point::new(self.p1.x as i32, self.p1.y as i32),
            Point::new(self.p2.x as i32, self.p2.y as i32),
        ).unwrap();
        renderer.set_draw_color(last);
    }
}

impl Primitive2D for Line {
    fn to_matrix(&self) -> Matrix {
        matrix!(
            [[self.p1.x,      self.p1.y,      1.0],
             [self.p2.x,      self.p2.y,      1.0],
             [self.average.x, self.average.y, 1.0]]
        )
    }

    fn from_matrix(&mut self, m: &Matrix) {
        self.p1      = Point2D { x: m.matrix[0][0], y: m.matrix[0][1] };
        self.p2      = Point2D { x: m.matrix[1][0], y: m.matrix[1][1] };
        self.average = Point2D { x: m.matrix[2][0], y: m.matrix[2][1] };
    }

    fn draw<F>(&self, set_pixel: F)
        where F: FnMut(i32, i32, Color) {
        self.draw_bresenham_line(set_pixel);
    }
}
