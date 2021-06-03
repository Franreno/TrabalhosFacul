from functools import reduce
from typing import final
from typing_extensions import runtime
from manim import *
from manim.utils import tex
from numpy import sqrt


def getLineRoot(x0,x1):
    try:
        m = abs( x1[1] - x0[1] ) / abs( x1[0] - x0[0] )
    except:
        return None

    root = ( m*x0[0] - x0[1] ) / m
    return [ root, 0, 0 ]    


class graphx(GraphScene):
    def __init__(self, **kwargs):
        GraphScene.__init__(
            self,
            x_min= 0,
            x_max = 9,
            y_min = -1.5,
            y_max = 1.5,
            graph_origin= 0.5*DOWN + 3*LEFT,
            axes_color=WHITE,
            **kwargs
        )  
    
    def writeText(self):
        text = Text("Método da Secante").move_to(UP)
        self.play(Write(text))
        self.wait(1)
        self.play(FadeOut(text))


    #Define graph functions
    def show_function_graph(self):
        self.setup_axes(animate=True)

        #math function
        def func(x):
            return np.cos(x)

        #define the actual graph
        graph = self.get_graph(func,x_min=3, x_max=7)
        graph.set_color(RED)

        x0 = Dot(radius=0.05).move_to(self.coords_to_point( 2*np.pi , func(2*np.pi)))    
        verticalx0dot = Dot(radius=0.05).move_to(self.coords_to_point(2*np.pi, 0))
        
        x1 = Dot(radius=0.05).move_to(self.coords_to_point( 5.5, func(5.5) ))
        verticalx1dot = Dot(radius=0.05).move_to(self.coords_to_point(5.5, 0))
        
        root = getLineRoot( [5.5, func(5.5)] , [2*np.pi , func(2*np.pi)] )
        rootdot = Dot(radius=0.05).move_to(self.coords_to_point( root[0], root[1] ) )
        
        line = Line(rootdot, x0).set_color(BLUE)
        


        linex1 = DashedLine(x1, verticalx1dot).set_color(GRAY)
        textVerticalx1 = Tex("$x_1$").next_to(verticalx1dot, DOWN)

        linex0 = DashedLine(x0, verticalx0dot).set_color(GRAY)
        textVerticalx0 = Tex("$x_0$").next_to(verticalx0dot, DOWN)

        textRootDot = Tex("$x_2$").next_to(rootdot, DOWN)

        self.play(Create(graph))
        self.wait(1)
        self.play(Create(x0),Create(x1),Create(rootdot))
        self.play(Create(line))
        self.play( Create(linex0), Write(textVerticalx0) , Create(linex1) , Write(textVerticalx1), Write(textRootDot),
        Create(verticalx1dot), Create(verticalx0dot))
        self.wait(1)
        self.play(FadeOut(graph) , FadeOut(self.axes))

        #draw First Triangle
        linex1x2 =  Line(rootdot, verticalx1dot).set_color(RED)
        linex1fx1 = Line(x1 , verticalx1dot ).set_color(RED)

        angle = Arc(
            radius=0.5,
            start_angle=linex1x2.get_angle(),
            angle=line.get_angle(),
            color=RED
        ).move_arc_center_to(self.coords_to_point(root[0], root[1]))
        
        textAngle = Tex("$\\alpha$").next_to(angle, RIGHT+0.01*UP)

        self.play(Create(linex1x2), Create(linex1fx1), Create(angle), Create(textAngle))


        eqTex = [
            Tex("$(x_1 - x_2)tan~\\alpha = f(x_1)$").move_to(3*LEFT + 2*UP),
            Tex("$x_1 - x_2 = \\frac{f(x_1)}{tan~\\alpha}$").move_to(3*LEFT + 1*UP),
            Tex("$tan~\\alpha = \\frac{f(x_1) - f(x_0)}{x_1 - x_0}$").move_to(3*LEFT - 1*UP),
            Tex("$x_2 = x_1 - f(x_1)\\frac{ x_1 - x_0}{ f(x_1) - f(x_0) }$").move_to(3*LEFT - 2*UP)
        ]

        self.play(Write(eqTex[0]))
        self.wait(1)
        self.play(Write(eqTex[1]))
        self.wait(1)

        #Draw second Triangle
        auxilaryDotx1x0 = Dot(radius=0.05).move_to(self.coords_to_point( 2*np.pi , func(5.5) ))

        linex1aux = Line(x1, auxilaryDotx1x0).set_color(GREEN)
        lineauxfx0 = Line(auxilaryDotx1x0, x0).set_color(GREEN)
        angle2 = Arc(
            radius=0.25,
            start_angle=linex1aux.get_angle(),
            angle = line.get_angle(),
            color=GREEN
        ).move_arc_center_to(self.coords_to_point( 5.5 , func(5.5) ) )
        
        textAngle2 = Tex("$\\alpha$").next_to(angle2, -0.05*RIGHT + 0.02 *UP ).scale(0.5)

        # textAngle.animate.next_to(angle)
        self.play( Create(linex1aux) , Create(lineauxfx0), Create(auxilaryDotx1x0), FadeOut(angle), FadeOut(textAngle))
        self.play(
            Create(angle2),
            Write(textAngle2)
        )
        self.wait(1)

        self.play(Write(eqTex[2]))
        self.wait(1)
        self.play(Write(eqTex[3]))
        self.wait(1)

        #Remove texts and draw back the graph

        self.play( 
            FadeOut(eqTex[0]), 
            FadeOut(eqTex[1]), 
            FadeOut(eqTex[2]), 
            FadeOut(eqTex[3]), 
            FadeOut(linex1x2),
            FadeOut(linex1fx1),
            FadeOut(angle2),
            FadeOut(textAngle2),
            FadeOut(linex1aux),    
            FadeOut(lineauxfx0),
            FadeOut(auxilaryDotx1x0)
        )
        self.setup_axes(animate=True)
        #draw back graph
        self.play(Create(graph))
        self.wait(1)

        #Get x3
        line.set_opacity(0.5)
        x3 = Dot(radius=0.05).move_to(self.coords_to_point( root[0] , func(root[0]) ))
        verticalx3dot = Dot(radius=0.05).move_to(self.coords_to_point(root[0] , 0))
        linex3 = DashedLine(x3, verticalx3dot).set_color(GRAY)
        textVerticalx3 = Tex("$x_2$").next_to(verticalx3dot, UP)

        self.play(FadeOut(rootdot) , FadeOut(textRootDot))
        self.wait(1)
        self.play( Create(x3), Create(linex3), Write(textVerticalx3) , Create(verticalx3dot))
        self.wait(1)

        #connect x3 to x1
        linex3x1 = Line(x3, x1).set_color(BLUE)
        self.play(Create(linex3x1))
        froot = getLineRoot( [root[0] , func(root[0]) ] , [5.5 , func(5.5)] )
        fdotroot = Dot(radius=0.05).move_to(self.coords_to_point(froot[0] , froot[1]) )
        fdotrootTex = Tex("$x_3$" ).next_to(fdotroot, UP)
        self.play(Create(fdotroot) , Write(fdotrootTex))
        self.wait(1)
        #fade out on everything
        self.play( 
            FadeOut(graph),
            FadeOut(line),
            FadeOut(linex3x1),
            FadeOut(linex3),
            FadeOut(verticalx3dot),
            FadeOut(x3),
            FadeOut(textVerticalx3),
            FadeOut(x1),
            FadeOut(x0),
            FadeOut(verticalx0dot),
            FadeOut(verticalx1dot),
            FadeOut(textVerticalx1),
            FadeOut(textVerticalx0),
            FadeOut(linex1),
            FadeOut(linex0),
            FadeOut(self.axes)
        )
        self.wait(1)

        finalTex = Tex("$x_{k+1} = x_k-f(x_k)\\frac{ x_k - x_{k-1}}{f(x_k)-f(x_{k-1})}$").move_to(3*LEFT + 1*UP)
        self.play(Write(finalTex))
        self.wait(2)
        self.play(FadeOut(fdotrootTex) , FadeOut(fdotroot), FadeOut(finalTex))
    
    #define construction
    def construct(self):
        self.writeText()
        self.show_function_graph()
        self.wait(1)