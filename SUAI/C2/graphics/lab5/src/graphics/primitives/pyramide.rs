use sdl2::pixels::Color;
use sdl2::render::Renderer;

use graphics::primitives::*;
use graphics::primitives::triangle::*;

#[derive(Debug)]
pub struct Pyramide {
    triangles: [Triangle; 6],
    anchor:  Point3,
    colors:  Vec<Color>
}

impl Pyramide {
    pub fn new(center: Point3, w: f64, h: f64, colors: Vec<Color>) -> Pyramide {
        use std::f64::*;

        let top = Point3::new(center.x, center.y - h / 2.0, center.z);
        let mut bottom = [Point3::new(0.0, 0.0, 0.0); 4];  

        // Bottom quad
        let by = center.y + h / 2.0;
        let radius = w / 2.0;
        for i in 0..4 {
            let fi = i as f64;
            bottom[i] = Point3::new(
                center.x + radius * (2.0 * consts::PI * fi / 4.0).cos(),
                by,
                center.z + radius * (2.0 * consts::PI * fi / 4.0).sin(),
            );
        }
        
        let mut triangle_ctr = 0;
        let mut next_color = || {
            triangle_ctr += 1;
            colors[triangle_ctr % colors.len()]
        };

        // Construct triangles 
        let triangles = [
            Triangle::new([top, bottom[0], bottom[1]],       center, next_color()),
            Triangle::new([top, bottom[1], bottom[2]],       center, next_color()),
            Triangle::new([top, bottom[2], bottom[3]],       center, next_color()),
            Triangle::new([top, bottom[3], bottom[0]],       center, next_color()),
            Triangle::new([bottom[0], bottom[2], bottom[1]], center, next_color()),
            Triangle::new([bottom[0], bottom[2], bottom[3]], center, next_color())
        ];

        Pyramide {
            triangles: triangles,
            anchor: center,
            colors: colors.clone()
        }
    }
}

impl Primitive3D for Pyramide {
    /* Getting figure triangles */
    fn triangles(&mut self) -> &mut [Triangle]             { &mut self.triangles[..] }

    /* Acnhor point is the local coordinates start point */
    fn anchor_point(&self) -> Point3                       { self.anchor }
    fn set_anchor_point(&mut self, anchor:  Point3)        { self.anchor = anchor; }

    fn fill(&mut self, renderer: &Renderer) {
        use std::cmp::Ordering;

        // Rearranging by Z axis
        self.triangles[..].sort_by(|t1, t2| {
            t1.midpoint().z.partial_cmp(&t2.midpoint().z).unwrap_or(Ordering::Equal)
        });

        for tri in &mut self.triangles {
            tri.fill(renderer);
        }
    }
}
