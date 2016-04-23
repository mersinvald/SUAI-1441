use sdl2::render::Renderer;

pub struct Point2D {
    pub x: i16,
    pub y: i16,
}

impl Point2D {
    pub fn new(x: i16, y: i16) -> Point2D {
        Point2D {
            x: x,
            y: y,
        }
    }
}

pub trait Primitive2D {
    fn draw(&self, renderer: &Renderer);
}
