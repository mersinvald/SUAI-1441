#![feature(step_by)]

extern crate sdl2;
extern crate sdl2_gfx;

use sdl2_gfx::primitives::DrawRenderer;
use sdl2::pixels::Color;
use sdl2::event::Event;
use std::time::Duration;

mod primitives;
mod circle;

use circle::*;
use primitives::*;

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
    fps_manager.set_framerate(10).unwrap();

    // Set draw color and clear the screen
    renderer.set_draw_color(Color::RGB(0, 0, 0));
    renderer.clear();
    renderer.present();

    // Get event pump
    let mut events = sdl_context.event_pump().unwrap();

    // Set first circle center and radius
    let startx1 = (WIDTH / 100 * 27) as f32;
    let startx2 = (WIDTH / 100 * 80) as f32;
    let starty  = (HEIGHT / 2)       as f32;

    // Set result text coordinates
    let textx = (WIDTH - 200) as i16;
    let texty = 10;
    // Create circles
    let mut bresenham_circles = Vec::with_capacity(80);
    let mut builtin_circles   = Vec::with_capacity(80);

    for r in (4..320).step_by(4) {
        bresenham_circles.push(
            Circle::new(
                Point2D::new(startx1, starty),
                r,
                Color::RGB(0, 255, 0)
            )
        );

        builtin_circles.push(
            Circle::new(
                Point2D::new(startx2, starty),
                r,
                Color::RGB(255, 0, 0)
            )
        );
    }

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

        // Clear render buffer
        renderer.set_draw_color(Color::RGB(0, 0, 0));
        renderer.clear();

        // Plot circles
        let builtin_duration = stopwatch(|| {
            for c in &builtin_circles {
                c.draw_builtin_circle(&renderer);
            }
        });

        let bresenham_duration = stopwatch(|| {
            for c in &bresenham_circles {
                c.draw(&renderer);
            }
        });

        let faster = if bresenham_duration.subsec_nanos() > builtin_duration.subsec_nanos() {
            "BUILTIN"
        } else {
            "MY IMPLEMENTATION"
        };

        // Draw results
        renderer.string(
            textx,
            texty,
            &format!("Bresenham: {} ms", bresenham_duration.subsec_nanos() / 1000_000),
            Color::RGB(255, 255, 255)
        ).unwrap();

        renderer.string(
            textx,
            texty + 15,
            &format!("Builtin:   {} ms", builtin_duration.subsec_nanos() / 1000_000),
            Color::RGB(255, 255, 255)
        ).unwrap();

        renderer.string(
            textx,
            texty + 30,
            &format!("Faster: {}", faster),
            Color::RGB(255, 255, 255)
        ).unwrap();

        // Present render buffer
        renderer.present();

        // Sleep until the next frame should be rendered
        fps_manager.delay();
    }
}

fn stopwatch<F>(mut closure: F) -> Duration
    where F: FnMut() {
    use std::time::SystemTime;
    let before_time = SystemTime::now();
    closure();
    let after_time  = SystemTime::now();
    after_time.duration_since(before_time).unwrap()
}
