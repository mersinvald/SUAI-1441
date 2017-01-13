use sdl2::pixels::Color;
use sdl2::render::Renderer;
use sdl2_gfx::primitives::DrawRenderer;
use cgmath::Transform;
use cgmath::Deg;
use cgmath::ortho;
use cgmath::prelude::EuclideanSpace;

use graphics::primitives::*;

#[derive(Debug, Copy, Clone)]
pub struct Triangle {
    points: [Point3; 3],
    projected: [Point3; 3],
    anchor: Point3, 
    color:  Color,
}

impl Triangle {
    pub fn new(points: [Point3; 3], anchor: Point3, color: Color) -> Triangle {
        Triangle {
            points: points,
            projected: [Point3::new(0.0, 0.0, 0.0); 3],
            anchor: anchor,
            color: color,
        }
    }

    pub fn project(&mut self) {
        let projection_matrix = ortho(0., 2., 0., 2., -1., 1.);
        for i in 0..3 {
            self.projected[i] = projection_matrix.transform_point(self.points[i]);
        }
    }

    pub fn midpoint(&self) -> Point3 {
        Point3::centroid(&self.points)
    }
}

impl Primitive3D for Triangle {
    /* Acnhor point is the local coordinates start point */
    fn anchor_point(&self) ->  Point3                      { self.anchor }
    fn set_anchor_point(&mut self, anchor: Point3)         { self.anchor = anchor }

    /* Draw the object on screen */
    fn draw(&mut self, renderer: &Renderer) { 
        self.project();
        renderer.trigon(
            self.projected[0].x as i16, self.projected[0].y as i16,
            self.projected[1].x as i16, self.projected[1].y as i16,
            self.projected[2].x as i16, self.projected[2].y as i16,
            self.color
        ).unwrap();
    }

    fn fill(&mut self, renderer: &Renderer) { 
        self.project();
        renderer.filled_trigon(
             self.projected[0].x as i16, self.projected[0].y as i16,
             self.projected[1].x as i16, self.projected[1].y as i16,
             self.projected[2].x as i16, self.projected[2].y as i16,
             self.color
        ).unwrap();
    }

    /* Affine Transformations */
    fn translate(&mut self, vector: Vector3) {
        let anchor = self.anchor_point();
        
        let norm_matrix = Matrix4::from_translation(Vector3::new(-anchor.x, -anchor.y, -anchor.z)); 
        let inv_norm_matrix = Matrix4::from_translation(Vector3::new(anchor.x, anchor.y, anchor.z));
        let trans_matrix = Matrix4::from_translation(vector);

        for i in 0..3 {
            self.points[i] = norm_matrix.transform_point(self.points[i]);
            self.points[i] = trans_matrix.transform_point(self.points[i]);
            self.points[i] = inv_norm_matrix.transform_point(self.points[i]);
        }

        // Moving anchor point by dx and dy
        self.anchor.x += vector.x;
        self.anchor.y += vector.y;
        self.anchor.z += vector.z;
    }

    fn scale(&mut self, vector: Vector3) {    
        let anchor = self.anchor_point();
        let norm_matrix = Matrix4::from_translation(Vector3::new(-anchor.x, -anchor.y, -anchor.z)); 
        let inv_norm_matrix = Matrix4::from_translation(Vector3::new(anchor.x, anchor.y, anchor.z));
        let scale_matrix = Matrix4::from_nonuniform_scale(vector.x, vector.y, vector.z);

        for i in 0..3 {
            self.points[i] = norm_matrix.transform_point(self.points[i]);
            self.points[i] = scale_matrix.transform_point(self.points[i]);
            self.points[i] = inv_norm_matrix.transform_point(self.points[i]);
        }
    }

    fn rotate(&mut self, vector: Vector3) {
        let anchor = self.anchor_point();
        let norm_matrix = Matrix4::from_translation(Vector3::new(-anchor.x, -anchor.y, -anchor.z)); 
        let inv_norm_matrix = Matrix4::from_translation(Vector3::new(anchor.x, anchor.y, anchor.z));
        let rot_matrix_x = Matrix4::from_angle_x(Deg(vector.x));
        let rot_matrix_y = Matrix4::from_angle_y(Deg(vector.y));
        let rot_matrix_z = Matrix4::from_angle_z(Deg(vector.z));

        for i in 0..3 {
            self.points[i] = norm_matrix.transform_point(self.points[i]);
            self.points[i] = rot_matrix_x.transform_point(self.points[i]);
            self.points[i] = rot_matrix_y.transform_point(self.points[i]);
            self.points[i] = rot_matrix_z.transform_point(self.points[i]);
            self.points[i] = inv_norm_matrix.transform_point(self.points[i]);
        }
    }
}