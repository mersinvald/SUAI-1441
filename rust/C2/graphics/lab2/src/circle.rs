use sdl2;
use sdl2::pixels::Color;
use sdl2::render::Renderer;
use sdl2_gfx::primitives::DrawRenderer;
use primitives::*;

pub struct Circle {
    center: Point2D,
    radius: i16,
    color:  Color
}

impl Circle {
    pub fn new(center: Point2D, radius: i16, color: Color) -> Circle {
        Circle {
            center: center,
            radius: radius,
            color:  color
        }
    }

    #[inline]
    pub fn draw_bresenham_circle(&self, renderer: &Renderer) {
        let x0 = self.center.x as i16;
        let y0 = self.center.y as i16;

        let mut x  = 0;
        let mut y  = self.radius;
        let mut dp = 1 - self.radius;

        while x < y+1 {
            renderer.pixel(x0 + x, y0 + y, self.color).unwrap();
            renderer.pixel(x0 - x, y0 + y, self.color).unwrap();
            renderer.pixel(x0 + x, y0 - y, self.color).unwrap();
            renderer.pixel(x0 - x, y0 - y, self.color).unwrap();
            renderer.pixel(x0 + y, y0 + x, self.color).unwrap();
            renderer.pixel(x0 - y, y0 + x, self.color).unwrap();
            renderer.pixel(x0 + y, y0 - x, self.color).unwrap();
            renderer.pixel(x0 - y, y0 - x, self.color).unwrap();

            x += 1;
            if dp < 0 {
                dp = dp + 2 * x + 3;
            } else {
                y -= 1;
                dp = dp + 2 * x - 2 * y + 5;
            }
        }
    }

    pub fn draw_builtin_circle(&self, renderer: &Renderer) {
        renderer.circle(
            self.center.x as i16,
            self.center.y as i16,
            self.radius,
            self.color
        ).unwrap();
    }
}

impl Primitive2D for Circle {
    #[inline]
    fn draw(&self, renderer: &sdl2::render::Renderer) {
        self.draw_bresenham_circle(renderer);
    }
}
