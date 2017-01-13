use cgmath;
use sdl2::render::Renderer;

pub type Point3  = cgmath::Point3<f64>;
pub type Matrix4 = cgmath::Matrix4<f64>;
pub type Vector3 = cgmath::Vector3<f64>;

pub mod pyramide;
pub mod triangle;

use triangle::Triangle;

#[allow(unused_variables)]
pub trait Primitive3D {
    /* Getting figure triangles */
    fn triangles(&mut self) -> &mut [Triangle]           { unimplemented!() }

    /* Acnhor point is the local coordinates start point */
    fn anchor_point(&self) -> Point3                     { unimplemented!() }
    fn set_anchor_point(&mut self, anchor: Point3)       { unimplemented!() }

    /* Draw the object on screen */
    fn draw(&mut self, renderer: &Renderer) { 
        for triangle in self.triangles() {
            triangle.draw(renderer);
        }
    }

    fn fill(&mut self, renderer: &Renderer) { 
        for triangle in self.triangles() {
            triangle.fill(renderer);
        }
     }

    /* Affine Transformations */
    fn translate(&mut self, vector: Vector3) {
        for triangle in self.triangles() {
            triangle.translate(vector);
        }

        // Moving anchor point by dx and dy
        let mut anchor = self.anchor_point();
        anchor.x += vector.x;
        anchor.y += vector.y;
        anchor.z += vector.z;
        self.set_anchor_point(anchor);
    }

    fn scale(&mut self, vector: Vector3) {    
        for triangle in self.triangles() {
            triangle.scale(vector);
        }
    }

    fn rotate(&mut self, vector: Vector3) {
        for triangle in self.triangles() {
            triangle.rotate(vector);
        }
    }
}
