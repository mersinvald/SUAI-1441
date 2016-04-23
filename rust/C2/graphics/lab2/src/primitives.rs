use sdl2::render::Renderer;

pub struct Point2D {
    pub x: f32,
    pub y: f32,
}

impl Point2D {
    pub fn new(x: f32, y: f32) -> Point2D {
        Point2D {
            x: x,
            y: y,
        }
    }
}

pub trait Primitive2D {
    fn draw(&self, renderer: &Renderer);
}
