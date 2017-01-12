extern crate sdl2;
extern crate sdl2_gfx;

use sdl2::pixels::Color;
use sdl2::event::Event;
use sdl2::keyboard::Scancode::*;

mod graphics;
use graphics::primitives::*;
use graphics::primitives::polygon::*;

const WIDTH: u32 = 1280;
const HEIGHT: u32 = 720;

fn main() {
    // Initialize SDL2
    let sdl_context   = sdl2::init().unwrap();
    let video_context = sdl_context.video().unwrap();

    // Create window
    let window = video_context.window("Graphics Task 1", WIDTH, HEIGHT)
        .position_centered()
        .opengl()
        .build()
        .unwrap();

    // Get renderer binded to window
    let mut renderer = window.renderer().build().unwrap();

    // Create FPS manager to precisely control inter-frames delays
    let mut fps_manager = sdl2_gfx::framerate::FPSManager::new();
    fps_manager.set_framerate(60).unwrap();

    // Set draw color and clear the screen
    renderer.set_draw_color(Color::RGB(0, 0, 0));
    renderer.clear();
    renderer.present();

    // Get event pump
    let mut events = sdl_context.event_pump().unwrap();

    let w0 = WIDTH as f32  / 100.0;
    let h0 = HEIGHT as f32 / 100.0;

    // Create polygons
    let mut polygons = vec![
        Polygon::new(&Point2D::new(w0 * 10.0, h0 * 50.0), 30.0,  3, Color::RGB(255, 0, 0)),
        Polygon::new(&Point2D::new(w0 * 25.0, h0 * 50.0), 50.0,  4, Color::RGB(0, 0, 255)),
        Polygon::new(&Point2D::new(w0 * 50.0, h0 * 50.0), 100.0, 6, Color::RGB(0, 255, 0)),
        Polygon::new(&Point2D::new(w0 * 75.0, h0 * 50.0), 50.0,  5, Color::RGB(0, 0, 255)),
        Polygon::new(&Point2D::new(w0 * 90.0, h0 * 50.0), 30.0,  3, Color::RGB(255, 0, 0)),
    ];

    // Start main loop
    'main:
    loop {
        // If exit event passed, break the loop
        for event in events.poll_iter() {
            match event {
                Event::Quit {..} => break 'main,
                _ => ()
            }
        }

        // Initialize variables
        let mut dx = 0.0;
        let mut dy = 0.0;
        let mut scale = 1.0;
        let mut angle = 0.0;
        let mut fill = false;

        // Poll presed keys
        for key in events.keyboard_state().pressed_scancodes() {
            match key {
                W       => dy -= 3.0,
                S       => dy += 3.0,
                D       => dx += 3.0,
                A       => dx -= 3.0,
                Up      => scale += 0.005,
                Down    => scale -= 0.005,
                Left    => angle -= 3.0,
                Right   => angle += 3.0,
                F       => fill = true,
                _       => (),
            }
        }

        // Clear render buffer
        renderer.set_draw_color(Color::RGB(0, 0, 0));
        renderer.clear();


        // Do affine transformations and draw
        for poly in &mut polygons {
            poly.translate(dx, dy);
            poly.rotate(angle);
            poly.scale(scale, scale);
            poly.draw(&renderer);
            if fill {
                poly.fill(&renderer);
            }
        }

        // Present render buffer
        renderer.present();

        // Sleep until the next frame should be rendered
        fps_manager.delay();
    }
}
