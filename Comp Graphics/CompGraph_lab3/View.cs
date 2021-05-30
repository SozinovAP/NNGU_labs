using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using OpenTK;
using OpenTK.Graphics.OpenGL;
namespace WindowsFormsApp1
{
    class View
    {
        private int BasicProgramID;
        private uint BasicVertexShader;
        private uint BasicFragmentShader;
        private Vector3[] vertdata;
        private int vbo_position;
        private int attribute_vpos;
        private int uniform_pos;
        private int uniform_aspect;
        private double aspect;

        private int CubMat = 0;
        private int NextCubMat = 1;
        private int BigSphereMat = 0;
        private int NextBigSphereMat = 1;
        private int SmallSphereMat = 0;
        private int NextSmallSphereMat = 1;
        private int ThetrMat = 0;
        private int NextThetrMat = 1;
        private int Depth = 0;
        private int NextDepth = 5;
        private float reflBS = 0;
        private float NextreflBS = 0.5f;
        private float refrBS = 0;
        private float NextrefrBS = 1.3f;
        private float reflSS = 0;
        private float NextreflSS = 0.5f;
        private float refrSS = 0;
        private float NextrefrSS = 1.5f;
        private float reflCub = 0;
        private float NextreflCub = 0.5f;
        private float refrCub = 0;
        private float NextrefrCub = 1f;
        private float reflT = 0;
        private float NextreflT = 0.5f;
        private float refrT = 0;
        private float NextrefrT = 1f;
        private Vector3 ColCub = new Vector3(0.0f, 0.0f, 0.0f);
        private Vector3 NextColCub = new Vector3(0.7f, 0.3f, 0.4f);
        private Vector3 ColBigSphere = new Vector3(0.0f, 0.0f, 0.0f);
        private Vector3 NextColBigSphere = new Vector3(0.5f, 0.5f, 0.5f); 
        private Vector3 ColSmallSphere = new Vector3(0.0f, 0.0f, 0.0f);
        private Vector3 NextColSmallSphere = new Vector3(0.5f, 0.5f, 0.5f); 
        private Vector3 ColThetr = new Vector3(0.0f, 0.0f, 0.0f);
        private Vector3 NextColThetr = new Vector3(0.3f, 0.1f, 0.5f);

        Vector3 cameraPosition = new Vector3(4, 3, 4);
        Vector3 cameraDirection = new Vector3(0, 0, 0);
        Vector3 CameraUp = new Vector3(0, 0, 1);
        public float latitude = 47.98f;
        public float longitude = 60.41f;
        public float radius = 5.385f;


        public void Setup(int width, int height)
        {
            GL.ClearColor(Color.DarkGray);          //заливка одним цветом
            GL.ShadeModel(ShadingModel.Smooth); //отрисовка с интерполяцией яркости
            GL.Enable(EnableCap.DepthTest);         //буфер глубины
        }

        public void Update()
        {
            cameraPosition = new Vector3(
                (float)(radius * Math.Cos(Math.PI / 180.0f * latitude) * Math.Cos(Math.PI / 180.0f * longitude)),
                (float)(radius * Math.Cos(Math.PI / 180.0f * latitude) * Math.Sin(Math.PI / 180.0f * longitude)),
                (float)(radius * Math.Sin(Math.PI / 180.0f * latitude)));

            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            Matrix4 viewMat = Matrix4.LookAt(cameraPosition, cameraDirection, CameraUp);
            GL.MatrixMode(MatrixMode.Modelview);
            GL.LoadMatrix(ref viewMat);
            Render();

        }
        public void Render()
        {
            GL.UseProgram(BasicProgramID);

            int location = GL.GetUniformLocation(BasicProgramID, "CubMat");
            if ((location != -1) && (NextCubMat != CubMat))
            {
                CubMat = NextCubMat;
                GL.Uniform1(location, CubMat);
            }
            location = GL.GetUniformLocation(BasicProgramID, "BigSphereMat");
            if ((location != -1) && (NextBigSphereMat != BigSphereMat))
            {
                BigSphereMat = NextBigSphereMat;
                GL.Uniform1(location, BigSphereMat);
            }
            location = GL.GetUniformLocation(BasicProgramID, "SmallSphereMat");
            if ((location != -1) && (NextSmallSphereMat != SmallSphereMat))
            {
                SmallSphereMat = NextSmallSphereMat;
                GL.Uniform1(location, SmallSphereMat);
            }
            location = GL.GetUniformLocation(BasicProgramID, "ThetrMat");
            if ((location != -1) && (NextThetrMat != ThetrMat))
            {
                ThetrMat = NextThetrMat;
                GL.Uniform1(location, ThetrMat);
            }
            location = GL.GetUniformLocation(BasicProgramID, "ColBigSphere");
            if ((location != -1) && (NextColBigSphere != ColBigSphere))
            {
                ColBigSphere = NextColBigSphere;
                GL.Uniform3(location, ColBigSphere.X, ColBigSphere.Y, ColBigSphere.Z);
            }
            location = GL.GetUniformLocation(BasicProgramID, "ColSmallSphere");
            if ((location != -1) && (NextColSmallSphere != ColSmallSphere))
            {
                ColSmallSphere = NextColSmallSphere;
                GL.Uniform3(location, ColSmallSphere.X, ColBigSphere.Y, ColSmallSphere.Z);
            }
            location = GL.GetUniformLocation(BasicProgramID, "ColCub");
            if ((location != -1) && (NextColCub != ColCub))
            {
                ColCub = NextColCub;
                GL.Uniform3(location, ColCub.X, ColCub.Y, ColCub.Z);
            }
            location = GL.GetUniformLocation(BasicProgramID, "ColThet");
            if ((location != -1) && (NextColThetr != ColThetr))
            {
                ColThetr = NextColThetr;
                GL.Uniform3(location, ColThetr.X, ColThetr.Y, ColThetr.Z);
            }
            location = GL.GetUniformLocation(BasicProgramID, "Depth");
            if ((location != -1) && (NextDepth != Depth))
            {
                Depth = NextDepth;
                GL.Uniform1(location, Depth);
            }

            location = GL.GetUniformLocation(BasicProgramID, "ReflCub");
            if ((location != -1) && (NextreflCub != reflCub))
            {
                reflCub = NextreflCub;
                GL.Uniform1(location, reflCub);
            }
            location = GL.GetUniformLocation(BasicProgramID, "RefrCub");
            if ((location != -1) && (NextrefrCub != refrCub))
            {
                refrCub = NextrefrCub;
                GL.Uniform1(location, refrCub);
            }
            location = GL.GetUniformLocation(BasicProgramID, "ReflBS");
            if ((location != -1) && (NextreflBS != reflBS))
            {
                reflBS = NextreflBS;
                GL.Uniform1(location, reflBS);
            }
            location = GL.GetUniformLocation(BasicProgramID, "RefrBS");
            if ((location != -1) && (NextrefrBS != refrBS))
            {
                refrBS = NextrefrBS;
                GL.Uniform1(location, refrBS);
            }
            location = GL.GetUniformLocation(BasicProgramID, "ReflSS");
            if ((location != -1) && (NextreflSS != reflSS))
            {
                reflSS = NextreflSS;
                GL.Uniform1(location, reflSS);
            }
            location = GL.GetUniformLocation(BasicProgramID, "RefrSS");
            if ((location != -1) && (NextrefrSS != refrSS))
            {
                refrSS = NextrefrSS;
                GL.Uniform1(location, refrSS);
            }
            location = GL.GetUniformLocation(BasicProgramID, "reflT");
            if ((location != -1) && (NextreflT != reflT))
            {
                reflT = NextreflT;
                GL.Uniform1(location, reflT);
            }
            location = GL.GetUniformLocation(BasicProgramID, "RefrT");
            if ((location != -1) && (NextrefrT != refrT))
            {
                refrT = NextrefrT;
                GL.Uniform1(location, refrT);
            }

            cameraPosition = new Vector3(1, 1, 3);
            vertdata = new Vector3[] {
                new Vector3(-1f, -1f, 0f),
                new Vector3( 1f, -1f, 0f),
                new Vector3( 1f, 1f, 0f),
                new Vector3(-1f, 1f, 0f) };
            GL.GenBuffers(1, out vbo_position);
            GL.BindBuffer(BufferTarget.ArrayBuffer, vbo_position);
            GL.BufferData<Vector3>(BufferTarget.ArrayBuffer, (IntPtr)(vertdata.Length *
                                                                      Vector3.SizeInBytes), vertdata, BufferUsageHint.StaticDraw);
            GL.VertexAttribPointer(attribute_vpos, 3, VertexAttribPointerType.Float, false, 0, 0);
           
            GL.Uniform3(uniform_pos, cameraPosition);
            GL.Uniform1(uniform_aspect, aspect);
            GL.UseProgram(BasicProgramID);
            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);

            GL.EnableClientState(ArrayCap.VertexArray);
            GL.BindBuffer(BufferTarget.ArrayBuffer, vbo_position);
            GL.VertexPointer(3, VertexPointerType.Float, Vector3.SizeInBytes, 0);

            GL.DrawArrays(PrimitiveType.Quads, 0, vertdata.Length);
           
        }

        public void SetCubView(int i)
        {
            NextCubMat = i;
        }

        public void SetBigSphere(int i)
        {
            NextBigSphereMat = i;
        }

        public void SetSmallSphere(int i)
        {
            NextSmallSphereMat = i;
        }

        public void SetDepth(int i)
        {
            NextDepth = i;
        }

        public void SetThetr(int i)
        {
            NextThetrMat = i;
        }

        public void SendFrontBack(int i)
        {
            int location = GL.GetUniformLocation(BasicProgramID, "FrontBack");
            if (location != -1)
            {
                GL.Uniform1(location, i);
            }
        }

        public void SendTopDown(int i)
        {
            int location = GL.GetUniformLocation(BasicProgramID, "TopDown");
            if (location != -1)
            {
                GL.Uniform1(location, i);
            }
        }

        public void SendLeftRight(int i)
        {
            int location = GL.GetUniformLocation(BasicProgramID, "LeftRight");
            if (location != -1)
            {
                GL.Uniform1(location, i);
            }
        }
        public void SetColCub(float x, float y, float z, float rl, float rr)
        {
            NextColCub = new Vector3(x, y, z);
            NextreflCub = rl;
            NextrefrCub = rr;
        }

        public void SetColBigSphere(float x, float y, float z, float rl, float rr)
        {
            NextColBigSphere = new Vector3(x, y, z);
            NextreflBS = rl;
            NextrefrBS = rr;
        }

        public void SetColSmallSphere(float x, float y, float z, float rl, float rr)
        {
            NextColSmallSphere = new Vector3(x, y, z);
            NextreflSS = rl;
            NextrefrSS = rr;
        }

        public void SetColThetr(float x, float y, float z, float rl, float rr)
        {
            NextColThetr = new Vector3(x, y, z);
            NextreflT = rl;
            NextrefrT = rr;
        }

        void loadShader(String filename, ShaderType type, uint program, out uint address)
        {
            address = (uint) GL.CreateShader(type);
            using (System.IO.StreamReader sr = new StreamReader(filename))
            {
                GL.ShaderSource((int) address, sr.ReadToEnd());
            }
            GL.CompileShader(address);
            GL.AttachShader(program, address);
            Console.WriteLine(GL.GetShaderInfoLog((int) address));
        }

        public void InitShader()
        {
            BasicProgramID = GL.CreateProgram(); // создание объекта программы
            loadShader("..\\..\\raytracing.vert", ShaderType.VertexShader, (uint) BasicProgramID,

                out BasicVertexShader);

            loadShader("..\\..\\raytracing.frag", ShaderType.FragmentShader, (uint) BasicProgramID,

                out BasicFragmentShader);
           
            int status = 0;

            GL.LinkProgram(BasicProgramID);
            // Проверяем успех компоновки

            GL.GetProgram(BasicProgramID, GetProgramParameterName.LinkStatus, out status);
            Console.WriteLine(GL.GetProgramInfoLog(BasicProgramID));
        }
    }
}
