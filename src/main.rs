use std::path::PathBuf;
use clap::arg_enum;
use structopt::StructOpt;

arg_enum! {
    #[derive(Debug)]
    enum OutputLanguage {
        Cpp,
        Rust,
    }
}

#[derive(Debug, StructOpt)]
#[structopt(name = "state_machine_gen", about = "Generate state machine framework from dot file")]
struct Opt {
    /// Activate debug mode
    #[structopt(short, long)]
    debug: bool,

    /// Select the output language
    #[structopt(short, long)]
    lang: OutputLanguage,

    /// Input file
    #[structopt(parse(from_os_str))]
    input: PathBuf,

    /// Output file, stdout if not present
    #[structopt(short = "o", long = "output", parse(from_os_str))]
    output: Option<PathBuf>,
}

fn main() {
    let opt = Opt::from_args();
    println!("{:?}", opt);
}
