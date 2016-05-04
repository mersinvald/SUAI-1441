use sdl2::render::Renderer;
use std;

pub mod face;
pub mod polygon;
pub mod line;

use graphics::math::matrix::Matrix;

#[derive(Debug)]
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

impl std::clone::Clone for Point2D {
    fn clone(&self) -> Point2D {
        Point2D::new(self.x, self.y)
    }
}

pub trait Primitive2D {
    /* Getting and setting via matrices, for affine transform */
    fn to_matrix(&self) -> Matrix;
    fn from_matrix(&mut self, m: &Matrix);

    /* Acnhor point is the local coordinates start point */
    fn anchor_point(&self) -> Point2D;
    fn set_anchor_point(&mut self, anchor: &Point2D);

    /* Affine Transformations */
    fn translate(&mut self, dx: f32, dy: f32) {
        let obj = self.to_matrix();
        let mut anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix(-anchor.x, -anchor.y) *
            Matrix::translation_matrix(dx, dy) *
            Matrix::translation_matrix(anchor.x, anchor.y))
        );

        // Moving anchor point by dx and dy
        anchor.x += dx;
        anchor.y += dy;

        self.set_anchor_point(&anchor);
    }

    fn scale(&mut self, sx: f32, sy: f32) {
        let obj = self.to_matrix();
        let anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix(-anchor.x, -anchor.y) *
            Matrix::scale_matrix(sx, sy) *
            Matrix::translation_matrix(anchor.x, anchor.y))
        );
    }

    fn rotate(&mut self, angle: f32) {
        let obj = self.to_matrix();
        let anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix(-anchor.x, -anchor.y) *
            Matrix::rotation_matrix(angle) *
            Matrix::translation_matrix(anchor.x, anchor.y))
        );
    }

    /* Draw the object on screen */
    fn draw(&self, renderer: &Renderer);

    fn fill(&self, renderer: &Renderer);
}
