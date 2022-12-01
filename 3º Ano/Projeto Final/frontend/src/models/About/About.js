import um from "../../assets/um.png";
import eeum from "../../assets/eeum.png";
import ecum from "../../assets/ecum.png";

export default function About() {
  return (
    <div className="mt-16 flex items-center flex-col">
      <class className="h-[40vh] sm:h-[50vh] w-screen text-green about-image"></class>
      <h1 className="text-6xl mt-4">About Us</h1>
      <div className="px-10 sm:w-[50%] sm:px-0 mt-6 text-xl text-justify">
        Created in 2022 by a group of students from the Degree in Computer
        Science at the University of Minho for the course unit project.
        ComputacionalMind was devised by teachers Pedro Rangel Henriques and
        Cristiana Araújo with the aim of bringing Computational Thinking to
        everyone, but especially to younger people, in order to prepare new
        generations for an increasingly computerised world.
      </div>
      <div className="my-6 flex justify-center items-center gap-x-10">
        <img src={ecum} className="aspect-auto w-[75px]" />
        <img src={um} className="aspect-auto w-[75px]" />
        <img src={eeum} className="aspect-auto w-[75px]" />
      </div>
    </div>
  );
}
