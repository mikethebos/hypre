/******************************************************************************
 * Copyright (c) 1998 Lawrence Livermore National Security, LLC and other
 * HYPRE Project Developers. See the top-level COPYRIGHT file for details.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR MIT)
 ******************************************************************************/

#include "_hypre_utilities.h"

/******************************************************************************
 * This routine is the same in both the sequential and normal cases
 *
 * The 'comm' argument for MPI_Comm_f2c is MPI_Fint, which is always the size of
 * a Fortran integer and hence usually the size of hypre_int.
 ****************************************************************************/

hypre_MPI_Comm
hypre_MPI_Comm_f2c( hypre_int comm )
{
#ifdef HYPRE_HAVE_MPI_COMM_F2C
   return (hypre_MPI_Comm) MPI_Comm_f2c(comm);
#else
   return (hypre_MPI_Comm) (size_t)comm;
#endif
}

/******************************************************************************
 * MPI stubs to generate serial codes without mpi
 *****************************************************************************/

#if defined(HYPRE_SEQUENTIAL)

HYPRE_Int
hypre_MPI_Init( hypre_int   *argc,
                char      ***argv )
{
   HYPRE_UNUSED_VAR(argc);
   HYPRE_UNUSED_VAR(argv);

   return (0);
}

HYPRE_Int
hypre_MPI_Finalize( void )
{
   return (0);
}

HYPRE_Int
hypre_MPI_Abort( hypre_MPI_Comm comm,
                 HYPRE_Int      errorcode )
{
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(errorcode);

   return (0);
}

HYPRE_Real
hypre_MPI_Wtime( void )
{
   return (0.0);
}

HYPRE_Real
hypre_MPI_Wtick( void )
{
   return (0.0);
}

HYPRE_Int
hypre_MPI_Barrier( hypre_MPI_Comm comm )
{
   HYPRE_UNUSED_VAR(comm);
   return (0);
}

HYPRE_Int
hypre_MPI_Comm_create( hypre_MPI_Comm   comm,
                       hypre_MPI_Group  group,
                       hypre_MPI_Comm  *newcomm )
{
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(group);
   *newcomm = hypre_MPI_COMM_NULL;
   return (0);
}

HYPRE_Int
hypre_MPI_Comm_dup( hypre_MPI_Comm  comm,
                    hypre_MPI_Comm *newcomm )
{
   *newcomm = comm;
   return (0);
}

HYPRE_Int
hypre_MPI_Comm_size( hypre_MPI_Comm  comm,
                     HYPRE_Int      *size )
{
   HYPRE_UNUSED_VAR(comm);
   *size = 1;
   return (0);
}

HYPRE_Int
hypre_MPI_Comm_rank( hypre_MPI_Comm  comm,
                     HYPRE_Int      *rank )
{
   HYPRE_UNUSED_VAR(comm);
   *rank = 0;
   return (0);
}

HYPRE_Int
hypre_MPI_Comm_free( hypre_MPI_Comm *comm )
{
   HYPRE_UNUSED_VAR(comm);
   return 0;
}

HYPRE_Int
hypre_MPI_Comm_group( hypre_MPI_Comm   comm,
                      hypre_MPI_Group *group )
{
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(group);
   return (0);
}

HYPRE_Int
hypre_MPI_Comm_split( hypre_MPI_Comm  comm,
                      HYPRE_Int       n,
                      HYPRE_Int       m,
                      hypre_MPI_Comm *comms )
{
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(n);
   HYPRE_UNUSED_VAR(m);
   HYPRE_UNUSED_VAR(comms);
   return (0);
}

HYPRE_Int
hypre_MPI_Group_incl( hypre_MPI_Group  group,
                      HYPRE_Int        n,
                      HYPRE_Int       *ranks,
                      hypre_MPI_Group *newgroup )
{
   HYPRE_UNUSED_VAR(group);
   HYPRE_UNUSED_VAR(n);
   HYPRE_UNUSED_VAR(ranks);
   HYPRE_UNUSED_VAR(newgroup);
   return (0);
}

HYPRE_Int
hypre_MPI_Group_free( hypre_MPI_Group *group )
{
   HYPRE_UNUSED_VAR(group);
   return 0;
}

HYPRE_Int
hypre_MPI_Address( void           *location,
                   hypre_MPI_Aint *address )
{
   HYPRE_UNUSED_VAR(location);
   HYPRE_UNUSED_VAR(address);
   return (0);
}

HYPRE_Int
hypre_MPI_Get_count( hypre_MPI_Status   *status,
                     hypre_MPI_Datatype  datatype,
                     HYPRE_Int          *count )
{
   HYPRE_UNUSED_VAR(status);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(count);
   return (0);
}

HYPRE_Int
hypre_MPI_Alltoall( void               *sendbuf,
                    HYPRE_Int           sendcount,
                    hypre_MPI_Datatype  sendtype,
                    void               *recvbuf,
                    HYPRE_Int           recvcount,
                    hypre_MPI_Datatype  recvtype,
                    hypre_MPI_Comm      comm )
{
   HYPRE_UNUSED_VAR(sendbuf);
   HYPRE_UNUSED_VAR(sendcount);
   HYPRE_UNUSED_VAR(sendtype);
   HYPRE_UNUSED_VAR(recvbuf);
   HYPRE_UNUSED_VAR(recvcount);
   HYPRE_UNUSED_VAR(recvtype);
   HYPRE_UNUSED_VAR(comm);
   return (0);
}

HYPRE_Int
hypre_MPI_Allgather( void               *sendbuf,
                     HYPRE_Int           sendcount,
                     hypre_MPI_Datatype  sendtype,
                     void               *recvbuf,
                     HYPRE_Int           recvcount,
                     hypre_MPI_Datatype  recvtype,
                     hypre_MPI_Comm      comm )
{
   HYPRE_Int i;

   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(recvcount);
   HYPRE_UNUSED_VAR(recvtype);
   switch (sendtype)
   {
      case hypre_MPI_INT:
      {
         HYPRE_Int *crecvbuf = (HYPRE_Int *)recvbuf;
         HYPRE_Int *csendbuf = (HYPRE_Int *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_LONG_LONG_INT:
      {
         HYPRE_BigInt *crecvbuf = (HYPRE_BigInt *)recvbuf;
         HYPRE_BigInt *csendbuf = (HYPRE_BigInt *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_FLOAT:
      {
         float *crecvbuf = (float *)recvbuf;
         float *csendbuf = (float *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_DOUBLE:
      {
         double *crecvbuf = (double *)recvbuf;
         double *csendbuf = (double *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_LONG_DOUBLE:
      {
         long double *crecvbuf = (long double *)recvbuf;
         long double *csendbuf = (long double *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_CHAR:
      {
         char *crecvbuf = (char *)recvbuf;
         char *csendbuf = (char *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_LONG:
      {
         hypre_longint *crecvbuf = (hypre_longint *)recvbuf;
         hypre_longint *csendbuf = (hypre_longint *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_BYTE:
      {
         hypre_TMemcpy(recvbuf, sendbuf, char, sendcount, HYPRE_MEMORY_HOST, HYPRE_MEMORY_HOST);
      }
      break;

      case hypre_MPI_REAL:
      {
         HYPRE_Real *crecvbuf = (HYPRE_Real *)recvbuf;
         HYPRE_Real *csendbuf = (HYPRE_Real *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_COMPLEX:
      {
         HYPRE_Complex *crecvbuf = (HYPRE_Complex *)recvbuf;
         HYPRE_Complex *csendbuf = (HYPRE_Complex *)sendbuf;
         for (i = 0; i < sendcount; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;
   }

   return (0);
}

HYPRE_Int
hypre_MPI_Allgatherv( void               *sendbuf,
                      HYPRE_Int           sendcount,
                      hypre_MPI_Datatype  sendtype,
                      void               *recvbuf,
                      HYPRE_Int          *recvcounts,
                      HYPRE_Int          *displs,
                      hypre_MPI_Datatype  recvtype,
                      hypre_MPI_Comm      comm )
{
   HYPRE_UNUSED_VAR(displs);
   return ( hypre_MPI_Allgather(sendbuf, sendcount, sendtype,
                                recvbuf, *recvcounts, recvtype, comm) );
}

HYPRE_Int
hypre_MPI_Gather( void               *sendbuf,
                  HYPRE_Int           sendcount,
                  hypre_MPI_Datatype  sendtype,
                  void               *recvbuf,
                  HYPRE_Int           recvcount,
                  hypre_MPI_Datatype  recvtype,
                  HYPRE_Int           root,
                  hypre_MPI_Comm      comm )
{
   HYPRE_UNUSED_VAR(root);
   return ( hypre_MPI_Allgather(sendbuf, sendcount, sendtype,
                                recvbuf, recvcount, recvtype, comm) );
}

HYPRE_Int
hypre_MPI_Gatherv( void              *sendbuf,
                   HYPRE_Int           sendcount,
                   hypre_MPI_Datatype  sendtype,
                   void               *recvbuf,
                   HYPRE_Int          *recvcounts,
                   HYPRE_Int          *displs,
                   hypre_MPI_Datatype  recvtype,
                   HYPRE_Int           root,
                   hypre_MPI_Comm      comm )
{
   HYPRE_UNUSED_VAR(displs);
   HYPRE_UNUSED_VAR(root);
   return ( hypre_MPI_Allgather(sendbuf, sendcount, sendtype,
                                recvbuf, *recvcounts, recvtype, comm) );
}

HYPRE_Int
hypre_MPI_Scatter( void               *sendbuf,
                   HYPRE_Int           sendcount,
                   hypre_MPI_Datatype  sendtype,
                   void               *recvbuf,
                   HYPRE_Int           recvcount,
                   hypre_MPI_Datatype  recvtype,
                   HYPRE_Int           root,
                   hypre_MPI_Comm      comm )
{
   HYPRE_UNUSED_VAR(root);
   return ( hypre_MPI_Allgather(sendbuf, sendcount, sendtype,
                                recvbuf, recvcount, recvtype, comm) );
}

HYPRE_Int
hypre_MPI_Scatterv( void               *sendbuf,
                    HYPRE_Int           *sendcounts,
                    HYPRE_Int           *displs,
                    hypre_MPI_Datatype   sendtype,
                    void                *recvbuf,
                    HYPRE_Int            recvcount,
                    hypre_MPI_Datatype   recvtype,
                    HYPRE_Int            root,
                    hypre_MPI_Comm       comm )
{
   HYPRE_UNUSED_VAR(displs);
   HYPRE_UNUSED_VAR(root);
   return ( hypre_MPI_Allgather(sendbuf, *sendcounts, sendtype,
                                recvbuf, recvcount, recvtype, comm) );
}

HYPRE_Int
hypre_MPI_Bcast( void               *buffer,
                 HYPRE_Int           count,
                 hypre_MPI_Datatype  datatype,
                 HYPRE_Int           root,
                 hypre_MPI_Comm      comm )
{
   HYPRE_UNUSED_VAR(buffer);
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(root);
   HYPRE_UNUSED_VAR(comm);
   return (0);
}

HYPRE_Int
hypre_MPI_Send( void               *buf,
                HYPRE_Int           count,
                hypre_MPI_Datatype  datatype,
                HYPRE_Int           dest,
                HYPRE_Int           tag,
                hypre_MPI_Comm      comm )
{
   HYPRE_UNUSED_VAR(buf);
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(dest);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   return (0);
}

HYPRE_Int
hypre_MPI_Recv( void               *buf,
                HYPRE_Int           count,
                hypre_MPI_Datatype  datatype,
                HYPRE_Int           source,
                HYPRE_Int           tag,
                hypre_MPI_Comm      comm,
                hypre_MPI_Status   *status )
{
   HYPRE_UNUSED_VAR(buf);
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(source);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(status);
   return (0);
}

HYPRE_Int
hypre_MPI_Isend( void               *buf,
                 HYPRE_Int           count,
                 hypre_MPI_Datatype  datatype,
                 HYPRE_Int           dest,
                 HYPRE_Int           tag,
                 hypre_MPI_Comm      comm,
                 hypre_MPI_Request  *request )
{
   HYPRE_UNUSED_VAR(buf);
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(dest);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(request);
   return (0);
}

HYPRE_Int
hypre_MPI_Irecv( void               *buf,
                 HYPRE_Int           count,
                 hypre_MPI_Datatype  datatype,
                 HYPRE_Int           source,
                 HYPRE_Int           tag,
                 hypre_MPI_Comm      comm,
                 hypre_MPI_Request  *request )
{
   HYPRE_UNUSED_VAR(buf);
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(source);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(request);
   return (0);
}

HYPRE_Int
hypre_MPI_Send_init( void               *buf,
                     HYPRE_Int           count,
                     hypre_MPI_Datatype  datatype,
                     HYPRE_Int           dest,
                     HYPRE_Int           tag,
                     hypre_MPI_Comm      comm,
                     hypre_MPI_Request  *request )
{
   HYPRE_UNUSED_VAR(buf);
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(dest);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(request);
   return 0;
}

HYPRE_Int
hypre_MPI_Recv_init( void               *buf,
                     HYPRE_Int           count,
                     hypre_MPI_Datatype  datatype,
                     HYPRE_Int           dest,
                     HYPRE_Int           tag,
                     hypre_MPI_Comm      comm,
                     hypre_MPI_Request  *request )
{
   HYPRE_UNUSED_VAR(buf);
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(dest);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(request);
   return 0;
}

HYPRE_Int
hypre_MPI_Irsend( void               *buf,
                  HYPRE_Int           count,
                  hypre_MPI_Datatype  datatype,
                  HYPRE_Int           dest,
                  HYPRE_Int           tag,
                  hypre_MPI_Comm      comm,
                  hypre_MPI_Request  *request )
{
   HYPRE_UNUSED_VAR(buf);
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(datatype);
   HYPRE_UNUSED_VAR(dest);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(request);
   return 0;
}

HYPRE_Int
hypre_MPI_Startall( HYPRE_Int          count,
                    hypre_MPI_Request *array_of_requests )
{
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(array_of_requests);
   return 0;
}

HYPRE_Int
hypre_MPI_Probe( HYPRE_Int         source,
                 HYPRE_Int         tag,
                 hypre_MPI_Comm    comm,
                 hypre_MPI_Status *status )
{
   HYPRE_UNUSED_VAR(source);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(status);
   return 0;
}

HYPRE_Int
hypre_MPI_Iprobe( HYPRE_Int         source,
                  HYPRE_Int         tag,
                  hypre_MPI_Comm    comm,
                  HYPRE_Int        *flag,
                  hypre_MPI_Status *status )
{
   HYPRE_UNUSED_VAR(source);
   HYPRE_UNUSED_VAR(tag);
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(flag);
   HYPRE_UNUSED_VAR(status);
   return 0;
}

HYPRE_Int
hypre_MPI_Test( hypre_MPI_Request *request,
                HYPRE_Int         *flag,
                hypre_MPI_Status  *status )
{
   HYPRE_UNUSED_VAR(request);
   HYPRE_UNUSED_VAR(status);
   *flag = 1;
   return (0);
}

HYPRE_Int
hypre_MPI_Testall( HYPRE_Int          count,
                   hypre_MPI_Request *array_of_requests,
                   HYPRE_Int         *flag,
                   hypre_MPI_Status  *array_of_statuses )
{
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(array_of_requests);
   HYPRE_UNUSED_VAR(flag);
   HYPRE_UNUSED_VAR(array_of_statuses);
   *flag = 1;
   return (0);
}

HYPRE_Int
hypre_MPI_Wait( hypre_MPI_Request *request,
                hypre_MPI_Status  *status )
{
   HYPRE_UNUSED_VAR(request);
   HYPRE_UNUSED_VAR(status);
   return (0);
}

HYPRE_Int
hypre_MPI_Waitall( HYPRE_Int          count,
                   hypre_MPI_Request *array_of_requests,
                   hypre_MPI_Status  *array_of_statuses )
{
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(array_of_requests);
   HYPRE_UNUSED_VAR(array_of_statuses);
   return (0);
}

HYPRE_Int
hypre_MPI_Waitany( HYPRE_Int          count,
                   hypre_MPI_Request *array_of_requests,
                   HYPRE_Int         *index,
                   hypre_MPI_Status  *status )
{
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(array_of_requests);
   HYPRE_UNUSED_VAR(index);
   HYPRE_UNUSED_VAR(status);
   return (0);
}

HYPRE_Int
hypre_MPI_Allreduce( void              *sendbuf,
                     void              *recvbuf,
                     HYPRE_Int          count,
                     hypre_MPI_Datatype datatype,
                     hypre_MPI_Op       op,
                     hypre_MPI_Comm     comm )
{
   HYPRE_Int i;

   HYPRE_UNUSED_VAR(op);
   HYPRE_UNUSED_VAR(comm);
   switch (datatype)
   {
      case hypre_MPI_INT:
      {
         HYPRE_Int *crecvbuf = (HYPRE_Int *)recvbuf;
         HYPRE_Int *csendbuf = (HYPRE_Int *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_LONG_LONG_INT:
      {
         HYPRE_BigInt *crecvbuf = (HYPRE_BigInt *)recvbuf;
         HYPRE_BigInt *csendbuf = (HYPRE_BigInt *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_FLOAT:
      {
         float *crecvbuf = (float *)recvbuf;
         float *csendbuf = (float *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_DOUBLE:
      {
         double *crecvbuf = (double *)recvbuf;
         double *csendbuf = (double *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_LONG_DOUBLE:
      {
         long double *crecvbuf = (long double *)recvbuf;
         long double *csendbuf = (long double *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_CHAR:
      {
         char *crecvbuf = (char *)recvbuf;
         char *csendbuf = (char *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_LONG:
      {
         hypre_longint *crecvbuf = (hypre_longint *)recvbuf;
         hypre_longint *csendbuf = (hypre_longint *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_BYTE:
      {
         hypre_TMemcpy(recvbuf, sendbuf, char, count, HYPRE_MEMORY_HOST, HYPRE_MEMORY_HOST);
      }
      break;

      case hypre_MPI_REAL:
      {
         HYPRE_Real *crecvbuf = (HYPRE_Real *)recvbuf;
         HYPRE_Real *csendbuf = (HYPRE_Real *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;

      case hypre_MPI_COMPLEX:
      {
         HYPRE_Complex *crecvbuf = (HYPRE_Complex *)recvbuf;
         HYPRE_Complex *csendbuf = (HYPRE_Complex *)sendbuf;
         for (i = 0; i < count; i++)
         {
            crecvbuf[i] = csendbuf[i];
         }
      }
      break;
   }

   return 0;
}

HYPRE_Int
hypre_MPI_Reduce( void               *sendbuf,
                  void               *recvbuf,
                  HYPRE_Int           count,
                  hypre_MPI_Datatype  datatype,
                  hypre_MPI_Op        op,
                  HYPRE_Int           root,
                  hypre_MPI_Comm      comm )
{
   HYPRE_UNUSED_VAR(root);
   hypre_MPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
   return 0;
}

HYPRE_Int
hypre_MPI_Scan( void               *sendbuf,
                void               *recvbuf,
                HYPRE_Int           count,
                hypre_MPI_Datatype  datatype,
                hypre_MPI_Op        op,
                hypre_MPI_Comm      comm )
{
   hypre_MPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
   return 0;
}

HYPRE_Int
hypre_MPI_Request_free( hypre_MPI_Request *request )
{
   HYPRE_UNUSED_VAR(request);
   return 0;
}

HYPRE_Int
hypre_MPI_Type_contiguous( HYPRE_Int           count,
                           hypre_MPI_Datatype  oldtype,
                           hypre_MPI_Datatype *newtype )
{
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(oldtype);
   HYPRE_UNUSED_VAR(newtype);
   return (0);
}

HYPRE_Int
hypre_MPI_Type_vector( HYPRE_Int           count,
                       HYPRE_Int           blocklength,
                       HYPRE_Int           stride,
                       hypre_MPI_Datatype  oldtype,
                       hypre_MPI_Datatype *newtype )
{
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(blocklength);
   HYPRE_UNUSED_VAR(stride);
   HYPRE_UNUSED_VAR(oldtype);
   HYPRE_UNUSED_VAR(newtype);
   return (0);
}

HYPRE_Int
hypre_MPI_Type_hvector( HYPRE_Int           count,
                        HYPRE_Int           blocklength,
                        hypre_MPI_Aint      stride,
                        hypre_MPI_Datatype  oldtype,
                        hypre_MPI_Datatype *newtype )
{
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(blocklength);
   HYPRE_UNUSED_VAR(stride);
   HYPRE_UNUSED_VAR(oldtype);
   HYPRE_UNUSED_VAR(newtype);
   return (0);
}

HYPRE_Int
hypre_MPI_Type_struct( HYPRE_Int           count,
                       HYPRE_Int          *array_of_blocklengths,
                       hypre_MPI_Aint     *array_of_displacements,
                       hypre_MPI_Datatype *array_of_types,
                       hypre_MPI_Datatype *newtype )
{
   HYPRE_UNUSED_VAR(count);
   HYPRE_UNUSED_VAR(array_of_blocklengths);
   HYPRE_UNUSED_VAR(array_of_displacements);
   HYPRE_UNUSED_VAR(array_of_types);
   HYPRE_UNUSED_VAR(newtype);
   return (0);
}

HYPRE_Int
hypre_MPI_Type_commit( hypre_MPI_Datatype *datatype )
{
   HYPRE_UNUSED_VAR(datatype);
   return (0);
}

HYPRE_Int
hypre_MPI_Type_free( hypre_MPI_Datatype *datatype )
{
   HYPRE_UNUSED_VAR(datatype);
   return (0);
}

HYPRE_Int
hypre_MPI_Op_create( hypre_MPI_User_function *function, hypre_int commute, hypre_MPI_Op *op )
{
   HYPRE_UNUSED_VAR(function);
   HYPRE_UNUSED_VAR(commute);
   HYPRE_UNUSED_VAR(op);
   return (0);
}

HYPRE_Int
hypre_MPI_Op_free( hypre_MPI_Op *op )
{
   HYPRE_UNUSED_VAR(op);
   return (0);
}

#if defined(HYPRE_USING_GPU)
HYPRE_Int hypre_MPI_Comm_split_type( hypre_MPI_Comm comm, HYPRE_Int split_type, HYPRE_Int key,
                                     hypre_MPI_Info info, hypre_MPI_Comm *newcomm )
{
   HYPRE_UNUSED_VAR(comm);
   HYPRE_UNUSED_VAR(split_type);
   HYPRE_UNUSED_VAR(key);
   HYPRE_UNUSED_VAR(info);
   HYPRE_UNUSED_VAR(newcomm);
   return (0);
}

HYPRE_Int hypre_MPI_Info_create( hypre_MPI_Info *info )
{
   HYPRE_UNUSED_VAR(info);
   return (0);
}

HYPRE_Int hypre_MPI_Info_free( hypre_MPI_Info *info )
{
   HYPRE_UNUSED_VAR(info);
   return (0);
}
#endif

/******************************************************************************
 * MPI stubs to do casting of HYPRE_Int and hypre_int correctly
 *****************************************************************************/

#else

// when updating NUM_MPIL_COMMS, update array initializations below
#define NUM_MPIL_COMMS 16

static MPI_Comm comms[NUM_MPIL_COMMS] = {MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL};
static MPI_Comm leader_group_comms[NUM_MPIL_COMMS] = {MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL};
static MPI_Comm leader_comms[NUM_MPIL_COMMS] = {MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL, MPI_COMM_NULL};
static int num_procss[NUM_MPIL_COMMS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int num_nodess[NUM_MPIL_COMMS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int ppns[NUM_MPIL_COMMS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

HYPRE_Int
hypre_MPI_Init( hypre_int   *argc,
                char      ***argv )
{
   HYPRE_Int out = (HYPRE_Int) MPI_Init(argc, argv);
   int found = 0;   
   comms[found] = MPI_COMM_WORLD;
   
   int rank, num_procs;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
   num_procss[found] = num_procs;
   
   // Split global comm into local (per node) communicators
   MPI_Comm local_comm;
   MPI_Comm_split_type(MPI_COMM_WORLD,
                        MPI_COMM_TYPE_SHARED,
                        rank,
                        MPI_INFO_NULL,
                        &local_comm);

   int local_rank, ppn;
   MPI_Comm_rank(local_comm, &local_rank);
   MPI_Comm_size(local_comm, &ppn);
   ppns[found] = ppn;

   // Split global comm into group (per local rank) communicators
   MPI_Comm group_comm;
   MPI_Comm_split(MPI_COMM_WORLD, local_rank, rank, &group_comm);

   int node;
   MPI_Comm_rank(group_comm, &node);

   // Gather arrays for get_node, get_local, and get_global methods
   // These arrays allow for these methods to work with any ordering
   // No longer relying on SMP ordering of processes to nodes!
   // Does rely on constant ppn
   int *global_rank_to_local = (int*)malloc(num_procs * sizeof(int));
   int *global_rank_to_node  = (int*)malloc(num_procs * sizeof(int));
   MPI_Allgather(&local_rank,
                  1,
                  MPI_INT,
                  global_rank_to_local,
                  1,
                  MPI_INT,
                  MPI_COMM_WORLD);
   MPI_Allgather(
      &node, 1, MPI_INT, global_rank_to_node, 1, MPI_INT, MPI_COMM_WORLD);

   int *ordered_global_ranks = (int*)malloc(num_procs * sizeof(int));
   for (int i = 0; i < num_procs; i++)
   {
      int local                                       = global_rank_to_local[i];
      int node                                        = global_rank_to_node[i];
      ordered_global_ranks[node * ppn + local] = i;
   }

   // Set xcomm variables
   int num_nodes = ((num_procs - 1) / ppn) + 1;
   num_nodess[found] = num_nodes;
   int rank_node = global_rank_to_node[rank];

   // Convert to leader_comm (4 leaders per node)
   int num_leaders = 4;
   int procs_per_leader = ppn / num_leaders;
   int leader = local_rank / procs_per_leader;
   int leader_rank = local_rank % procs_per_leader;

   MPI_Comm leader_comm;
   MPI_Comm_split(
      local_comm, local_rank / procs_per_leader, rank, &leader_comm);
      
   leader_comms[found] = leader_comm;
      
   MPI_Comm leader_group_comm;
   MPI_Comm_split(MPI_COMM_WORLD, leader_rank, rank, &leader_group_comm);
   
   leader_group_comms[found] = leader_group_comm;
   
   free((void *)ordered_global_ranks);
   free((void *)global_rank_to_local);
   free((void *)global_rank_to_node);
   MPI_Comm_free(&group_comm);
   MPI_Comm_free(&local_comm);
   
   return out;
}

HYPRE_Int
hypre_MPI_Finalize( void )
{
   for (int i = 0; i < NUM_MPIL_COMMS; ++i)
   {
      comms[i] = MPI_COMM_NULL;
      if (leader_group_comms[i] != MPI_COMM_NULL) MPI_Comm_free(&(leader_group_comms[i]));
      leader_group_comms[i] = MPI_COMM_NULL;
      if (leader_comms[i] != MPI_COMM_NULL) MPI_Comm_free(&(leader_comms[i]));
      leader_comms[i] = MPI_COMM_NULL;
   }
   
   return (HYPRE_Int) MPI_Finalize();
}

HYPRE_Int
hypre_MPI_Abort( hypre_MPI_Comm comm,
                 HYPRE_Int      errorcode )
{
   return (HYPRE_Int) MPI_Abort(comm, (hypre_int)errorcode);
}

HYPRE_Real
hypre_MPI_Wtime( void )
{
   return (HYPRE_Real)MPI_Wtime();
}

HYPRE_Real
hypre_MPI_Wtick( void )
{
   return (HYPRE_Real)MPI_Wtick();
}

HYPRE_Int
hypre_MPI_Barrier( hypre_MPI_Comm comm )
{
   return (HYPRE_Int) MPI_Barrier(comm);
}

HYPRE_Int
hypre_MPI_Comm_create( hypre_MPI_Comm   comm,
                       hypre_MPI_Group  group,
                       hypre_MPI_Comm  *newcomm )
{
   return (HYPRE_Int) MPI_Comm_create(comm, group, newcomm);
}

HYPRE_Int
hypre_MPI_Comm_dup( hypre_MPI_Comm  comm,
                    hypre_MPI_Comm *newcomm )
{
   return (HYPRE_Int) MPI_Comm_dup(comm, newcomm);
}

HYPRE_Int
hypre_MPI_Comm_size( hypre_MPI_Comm  comm,
                     HYPRE_Int      *size )
{
   hypre_int mpi_size;
   HYPRE_Int ierr;
   ierr = (HYPRE_Int) MPI_Comm_size(comm, &mpi_size);
   *size = (HYPRE_Int) mpi_size;
   return ierr;
}

HYPRE_Int
hypre_MPI_Comm_rank( hypre_MPI_Comm  comm,
                     HYPRE_Int      *rank )
{
   hypre_int mpi_rank;
   HYPRE_Int ierr;
   ierr = (HYPRE_Int) MPI_Comm_rank(comm, &mpi_rank);
   *rank = (HYPRE_Int) mpi_rank;
   return ierr;
}

HYPRE_Int
hypre_MPI_Comm_free( hypre_MPI_Comm *comm )
{
   return (HYPRE_Int) MPI_Comm_free(comm);
}

HYPRE_Int
hypre_MPI_Comm_group( hypre_MPI_Comm   comm,
                      hypre_MPI_Group *group )
{
   return (HYPRE_Int) MPI_Comm_group(comm, group);
}

HYPRE_Int
hypre_MPI_Comm_split( hypre_MPI_Comm  comm,
                      HYPRE_Int       n,
                      HYPRE_Int       m,
                      hypre_MPI_Comm *comms )
{
   return (HYPRE_Int) MPI_Comm_split(comm, (hypre_int)n, (hypre_int)m, comms);
}

HYPRE_Int
hypre_MPI_Group_incl( hypre_MPI_Group  group,
                      HYPRE_Int        n,
                      HYPRE_Int       *ranks,
                      hypre_MPI_Group *newgroup )
{
   hypre_int *mpi_ranks;
   HYPRE_Int  i;
   HYPRE_Int  ierr;

   mpi_ranks = hypre_TAlloc(hypre_int,  n, HYPRE_MEMORY_HOST);
   for (i = 0; i < n; i++)
   {
      mpi_ranks[i] = (hypre_int) ranks[i];
   }
   ierr = (HYPRE_Int) MPI_Group_incl(group, (hypre_int)n, mpi_ranks, newgroup);
   hypre_TFree(mpi_ranks, HYPRE_MEMORY_HOST);

   return ierr;
}

HYPRE_Int
hypre_MPI_Group_free( hypre_MPI_Group *group )
{
   return (HYPRE_Int) MPI_Group_free(group);
}

HYPRE_Int
hypre_MPI_Address( void           *location,
                   hypre_MPI_Aint *address )
{
#if MPI_VERSION > 1
   return (HYPRE_Int) MPI_Get_address(location, address);
#else
   return (HYPRE_Int) MPI_Address(location, address);
#endif
}

HYPRE_Int
hypre_MPI_Get_count( hypre_MPI_Status   *status,
                     hypre_MPI_Datatype  datatype,
                     HYPRE_Int          *count )
{
   hypre_int mpi_count;
   HYPRE_Int ierr;
   ierr = (HYPRE_Int) MPI_Get_count(status, datatype, &mpi_count);
   *count = (HYPRE_Int) mpi_count;
   return ierr;
}

HYPRE_Int
hypre_MPI_Alltoall( void               *sendbuf,
                    HYPRE_Int           sendcount,
                    hypre_MPI_Datatype  sendtype,
                    void               *recvbuf,
                    HYPRE_Int           recvcount,
                    hypre_MPI_Datatype  recvtype,
                    hypre_MPI_Comm      comm )
{
   return (HYPRE_Int) MPI_Alltoall(sendbuf, (hypre_int)sendcount, sendtype,
                                   recvbuf, (hypre_int)recvcount, recvtype, comm);
}

HYPRE_Int
hypre_MPI_Allgather( void               *sendbuf,
                     HYPRE_Int           sendcount,
                     hypre_MPI_Datatype  sendtype,
                     void               *recvbuf,
                     HYPRE_Int           recvcount,
                     hypre_MPI_Datatype  recvtype,
                     hypre_MPI_Comm      comm )
{
   return (HYPRE_Int) MPI_Allgather(sendbuf, (hypre_int)sendcount, sendtype,
                                    recvbuf, (hypre_int)recvcount, recvtype, comm);
}

HYPRE_Int
hypre_MPI_Allgatherv( void               *sendbuf,
                      HYPRE_Int           sendcount,
                      hypre_MPI_Datatype  sendtype,
                      void               *recvbuf,
                      HYPRE_Int          *recvcounts,
                      HYPRE_Int          *displs,
                      hypre_MPI_Datatype  recvtype,
                      hypre_MPI_Comm      comm )
{
   hypre_int *mpi_recvcounts, *mpi_displs, csize;
   HYPRE_Int  i;
   HYPRE_Int  ierr;

   MPI_Comm_size(comm, &csize);
   mpi_recvcounts = hypre_TAlloc(hypre_int, csize, HYPRE_MEMORY_HOST);
   mpi_displs = hypre_TAlloc(hypre_int, csize, HYPRE_MEMORY_HOST);
   for (i = 0; i < csize; i++)
   {
      mpi_recvcounts[i] = (hypre_int) recvcounts[i];
      mpi_displs[i] = (hypre_int) displs[i];
   }
   ierr = (HYPRE_Int) MPI_Allgatherv(sendbuf, (hypre_int)sendcount, sendtype,
                                     recvbuf, mpi_recvcounts, mpi_displs,
                                     recvtype, comm);
   hypre_TFree(mpi_recvcounts, HYPRE_MEMORY_HOST);
   hypre_TFree(mpi_displs, HYPRE_MEMORY_HOST);

   return ierr;
}

HYPRE_Int
hypre_MPI_Gather( void               *sendbuf,
                  HYPRE_Int           sendcount,
                  hypre_MPI_Datatype  sendtype,
                  void               *recvbuf,
                  HYPRE_Int           recvcount,
                  hypre_MPI_Datatype  recvtype,
                  HYPRE_Int           root,
                  hypre_MPI_Comm      comm )
{
   return (HYPRE_Int) MPI_Gather(sendbuf, (hypre_int) sendcount, sendtype,
                                 recvbuf, (hypre_int) recvcount, recvtype,
                                 (hypre_int)root, comm);
}

HYPRE_Int
hypre_MPI_Gatherv(void               *sendbuf,
                  HYPRE_Int           sendcount,
                  hypre_MPI_Datatype  sendtype,
                  void               *recvbuf,
                  HYPRE_Int          *recvcounts,
                  HYPRE_Int          *displs,
                  hypre_MPI_Datatype  recvtype,
                  HYPRE_Int           root,
                  hypre_MPI_Comm      comm )
{
   hypre_int *mpi_recvcounts = NULL;
   hypre_int *mpi_displs = NULL;
   hypre_int csize, croot;
   HYPRE_Int  i;
   HYPRE_Int  ierr;

   MPI_Comm_size(comm, &csize);
   MPI_Comm_rank(comm, &croot);
   if (croot == (hypre_int) root)
   {
      mpi_recvcounts = hypre_TAlloc(hypre_int,  csize, HYPRE_MEMORY_HOST);
      mpi_displs = hypre_TAlloc(hypre_int,  csize, HYPRE_MEMORY_HOST);
      for (i = 0; i < csize; i++)
      {
         mpi_recvcounts[i] = (hypre_int) recvcounts[i];
         mpi_displs[i] = (hypre_int) displs[i];
      }
   }
   ierr = (HYPRE_Int) MPI_Gatherv(sendbuf, (hypre_int)sendcount, sendtype,
                                  recvbuf, mpi_recvcounts, mpi_displs,
                                  recvtype, (hypre_int) root, comm);
   hypre_TFree(mpi_recvcounts, HYPRE_MEMORY_HOST);
   hypre_TFree(mpi_displs, HYPRE_MEMORY_HOST);

   return ierr;
}

HYPRE_Int
hypre_MPI_Scatter( void               *sendbuf,
                   HYPRE_Int           sendcount,
                   hypre_MPI_Datatype  sendtype,
                   void               *recvbuf,
                   HYPRE_Int           recvcount,
                   hypre_MPI_Datatype  recvtype,
                   HYPRE_Int           root,
                   hypre_MPI_Comm      comm )
{
   return (HYPRE_Int) MPI_Scatter(sendbuf, (hypre_int)sendcount, sendtype,
                                  recvbuf, (hypre_int)recvcount, recvtype,
                                  (hypre_int)root, comm);
}

HYPRE_Int
hypre_MPI_Scatterv(void               *sendbuf,
                   HYPRE_Int          *sendcounts,
                   HYPRE_Int          *displs,
                   hypre_MPI_Datatype  sendtype,
                   void               *recvbuf,
                   HYPRE_Int           recvcount,
                   hypre_MPI_Datatype  recvtype,
                   HYPRE_Int           root,
                   hypre_MPI_Comm      comm )
{
   hypre_int *mpi_sendcounts = NULL;
   hypre_int *mpi_displs = NULL;
   hypre_int csize, croot;
   HYPRE_Int  i;
   HYPRE_Int  ierr;

   MPI_Comm_size(comm, &csize);
   MPI_Comm_rank(comm, &croot);
   if (croot == (hypre_int) root)
   {
      mpi_sendcounts = hypre_TAlloc(hypre_int,  csize, HYPRE_MEMORY_HOST);
      mpi_displs = hypre_TAlloc(hypre_int,  csize, HYPRE_MEMORY_HOST);
      for (i = 0; i < csize; i++)
      {
         mpi_sendcounts[i] = (hypre_int) sendcounts[i];
         mpi_displs[i] = (hypre_int) displs[i];
      }
   }
   ierr = (HYPRE_Int) MPI_Scatterv(sendbuf, mpi_sendcounts, mpi_displs, sendtype,
                                   recvbuf, (hypre_int) recvcount,
                                   recvtype, (hypre_int) root, comm);
   hypre_TFree(mpi_sendcounts, HYPRE_MEMORY_HOST);
   hypre_TFree(mpi_displs, HYPRE_MEMORY_HOST);

   return ierr;
}

HYPRE_Int
hypre_MPI_Bcast( void               *buffer,
                 HYPRE_Int           count,
                 hypre_MPI_Datatype  datatype,
                 HYPRE_Int           root,
                 hypre_MPI_Comm      comm )
{
   return (HYPRE_Int) MPI_Bcast(buffer, (hypre_int)count, datatype,
                                (hypre_int)root, comm);
}

HYPRE_Int
hypre_MPI_Send( void               *buf,
                HYPRE_Int           count,
                hypre_MPI_Datatype  datatype,
                HYPRE_Int           dest,
                HYPRE_Int           tag,
                hypre_MPI_Comm      comm )
{
   return (HYPRE_Int) MPI_Send(buf, (hypre_int)count, datatype,
                               (hypre_int)dest, (hypre_int)tag, comm);
}

HYPRE_Int
hypre_MPI_Recv( void               *buf,
                HYPRE_Int           count,
                hypre_MPI_Datatype  datatype,
                HYPRE_Int           source,
                HYPRE_Int           tag,
                hypre_MPI_Comm      comm,
                hypre_MPI_Status   *status )
{
   return (HYPRE_Int) MPI_Recv(buf, (hypre_int)count, datatype,
                               (hypre_int)source, (hypre_int)tag, comm, status);
}

HYPRE_Int
hypre_MPI_Isend( void               *buf,
                 HYPRE_Int           count,
                 hypre_MPI_Datatype  datatype,
                 HYPRE_Int           dest,
                 HYPRE_Int           tag,
                 hypre_MPI_Comm      comm,
                 hypre_MPI_Request  *request )
{
   return (HYPRE_Int) MPI_Isend(buf, (hypre_int)count, datatype,
                                (hypre_int)dest, (hypre_int)tag, comm, request);
}

HYPRE_Int
hypre_MPI_Irecv( void               *buf,
                 HYPRE_Int           count,
                 hypre_MPI_Datatype  datatype,
                 HYPRE_Int           source,
                 HYPRE_Int           tag,
                 hypre_MPI_Comm      comm,
                 hypre_MPI_Request  *request )
{
   return (HYPRE_Int) MPI_Irecv(buf, (hypre_int)count, datatype,
                                (hypre_int)source, (hypre_int)tag, comm, request);
}

HYPRE_Int
hypre_MPI_Send_init( void               *buf,
                     HYPRE_Int           count,
                     hypre_MPI_Datatype  datatype,
                     HYPRE_Int           dest,
                     HYPRE_Int           tag,
                     hypre_MPI_Comm      comm,
                     hypre_MPI_Request  *request )
{
   return (HYPRE_Int) MPI_Send_init(buf, (hypre_int)count, datatype,
                                    (hypre_int)dest, (hypre_int)tag,
                                    comm, request);
}

HYPRE_Int
hypre_MPI_Recv_init( void               *buf,
                     HYPRE_Int           count,
                     hypre_MPI_Datatype  datatype,
                     HYPRE_Int           dest,
                     HYPRE_Int           tag,
                     hypre_MPI_Comm      comm,
                     hypre_MPI_Request  *request )
{
   return (HYPRE_Int) MPI_Recv_init(buf, (hypre_int)count, datatype,
                                    (hypre_int)dest, (hypre_int)tag,
                                    comm, request);
}

HYPRE_Int
hypre_MPI_Irsend( void               *buf,
                  HYPRE_Int           count,
                  hypre_MPI_Datatype  datatype,
                  HYPRE_Int           dest,
                  HYPRE_Int           tag,
                  hypre_MPI_Comm      comm,
                  hypre_MPI_Request  *request )
{
   return (HYPRE_Int) MPI_Irsend(buf, (hypre_int)count, datatype,
                                 (hypre_int)dest, (hypre_int)tag, comm, request);
}

HYPRE_Int
hypre_MPI_Startall( HYPRE_Int          count,
                    hypre_MPI_Request *array_of_requests )
{
   return (HYPRE_Int) MPI_Startall((hypre_int)count, array_of_requests);
}

HYPRE_Int
hypre_MPI_Probe( HYPRE_Int         source,
                 HYPRE_Int         tag,
                 hypre_MPI_Comm    comm,
                 hypre_MPI_Status *status )
{
   return (HYPRE_Int) MPI_Probe((hypre_int)source, (hypre_int)tag, comm, status);
}

HYPRE_Int
hypre_MPI_Iprobe( HYPRE_Int         source,
                  HYPRE_Int         tag,
                  hypre_MPI_Comm    comm,
                  HYPRE_Int        *flag,
                  hypre_MPI_Status *status )
{
   hypre_int mpi_flag;
   HYPRE_Int ierr;
   ierr = (HYPRE_Int) MPI_Iprobe((hypre_int)source, (hypre_int)tag, comm,
                                 &mpi_flag, status);
   *flag = (HYPRE_Int) mpi_flag;
   return ierr;
}

HYPRE_Int
hypre_MPI_Test( hypre_MPI_Request *request,
                HYPRE_Int         *flag,
                hypre_MPI_Status  *status )
{
   hypre_int mpi_flag;
   HYPRE_Int ierr;
   ierr = (HYPRE_Int) MPI_Test(request, &mpi_flag, status);
   *flag = (HYPRE_Int) mpi_flag;
   return ierr;
}

HYPRE_Int
hypre_MPI_Testall( HYPRE_Int          count,
                   hypre_MPI_Request *array_of_requests,
                   HYPRE_Int         *flag,
                   hypre_MPI_Status  *array_of_statuses )
{
   hypre_int mpi_flag;
   HYPRE_Int ierr;
   ierr = (HYPRE_Int) MPI_Testall((hypre_int)count, array_of_requests,
                                  &mpi_flag, array_of_statuses);
   *flag = (HYPRE_Int) mpi_flag;
   return ierr;
}

HYPRE_Int
hypre_MPI_Wait( hypre_MPI_Request *request,
                hypre_MPI_Status  *status )
{
   return (HYPRE_Int) MPI_Wait(request, status);
}

HYPRE_Int
hypre_MPI_Waitall( HYPRE_Int          count,
                   hypre_MPI_Request *array_of_requests,
                   hypre_MPI_Status  *array_of_statuses )
{
   return (HYPRE_Int) MPI_Waitall((hypre_int)count,
                                  array_of_requests, array_of_statuses);
}

HYPRE_Int
hypre_MPI_Waitany( HYPRE_Int          count,
                   hypre_MPI_Request *array_of_requests,
                   HYPRE_Int         *index,
                   hypre_MPI_Status  *status )
{
   hypre_int mpi_index;
   HYPRE_Int ierr;
   ierr = (HYPRE_Int) MPI_Waitany((hypre_int)count, array_of_requests,
                                  &mpi_index, status);
   *index = (HYPRE_Int) mpi_index;
   return ierr;
}

int allreduce_dissemination_loc_core(
                        const void* sendbuf,
                        void* recvbuf,
                        int count,
                        MPI_Datatype datatype,
                        MPI_Op op,
                        MPI_Comm global_comm, 
                        MPI_Comm group_comm,
                        MPI_Comm local_comm,
                        int tag)
{
    int type_size;
    MPI_Type_size(datatype, &type_size);
    
    char *cpu_sendbuf = (char *)malloc(count*type_size);
    char *cpu_recvbuf = (char *)malloc(count*type_size);

    int rank, num_procs;
    MPI_Comm_rank(global_comm, &rank);
    MPI_Comm_size(global_comm, &num_procs);
    
    // to work on gpus and cpus
    MPI_Sendrecv(sendbuf, count, datatype, rank, tag, cpu_sendbuf, count, datatype, rank, tag, global_comm, MPI_STATUS_IGNORE);

    int local_rank, ppn;
    MPI_Comm_rank(local_comm, &local_rank);
    MPI_Comm_size(local_comm, &ppn);

    int rank_node, num_nodes;
    MPI_Comm_rank(group_comm, &rank_node);
    MPI_Comm_size(group_comm, &num_nodes);

    PMPI_Allreduce(cpu_sendbuf, cpu_recvbuf, count, datatype,
            op, local_comm);

    int pow_ppn_num_nodes = 1;
    int base = ppn + 1;
    while (pow_ppn_num_nodes * base <= num_nodes)
        pow_ppn_num_nodes *= base;
    int mult = num_nodes / pow_ppn_num_nodes;
    int max_node = mult * pow_ppn_num_nodes;
    int extra = num_nodes - max_node;

    void *tmpbuf = (void *)malloc(type_size*count);

    if (rank_node >= max_node)
    {
        int node = rank_node - max_node;
        MPI_Send(cpu_recvbuf, count, datatype, node, tag, group_comm);
        MPI_Recv(cpu_recvbuf, count, datatype, node, tag, group_comm,
                MPI_STATUS_IGNORE);
    }
    else
    {
        if (rank_node < extra)
        {
            MPI_Recv(tmpbuf, count, datatype, max_node + rank_node, tag, group_comm,
                   MPI_STATUS_IGNORE);
            MPI_Reduce_local(tmpbuf, cpu_recvbuf, count, datatype, op);
        }

        for (int node_stride = 1; node_stride < max_node; node_stride *= (ppn+1))
        {
            int stride = node_stride * (local_rank+1);
            if (stride < max_node)
            {
                int send_node = (rank_node - stride + max_node) % max_node;
                int recv_node = (rank_node + stride) % max_node;
                MPI_Sendrecv(cpu_recvbuf, count, datatype, send_node, tag,
                        tmpbuf, count, datatype, recv_node, tag,
                        group_comm, MPI_STATUS_IGNORE);
            }
            else
            {
                // Odd implementation to be portable to GPU
                // Can have zerobuf be on CPU, regardless of
                // where tmpbuf is located
                char* zerobuf = (char*)malloc(type_size*count);
                memset(zerobuf, 0, type_size*count);
                MPI_Sendrecv(zerobuf, count, datatype, rank, tag,
                        tmpbuf, count, datatype, rank, tag,
                        global_comm, MPI_STATUS_IGNORE);
                free(zerobuf);
            }
            PMPI_Allreduce(MPI_IN_PLACE, tmpbuf, count, datatype, op, local_comm);
            MPI_Reduce_local(tmpbuf, cpu_recvbuf, count, datatype, op);
        }

        if (rank_node < extra)
        {
            MPI_Send(cpu_recvbuf, count, datatype, max_node + rank_node, tag, group_comm);
        }
    }

    free((void*)tmpbuf);
    
    // to work on gpus and cpus
    MPI_Sendrecv(cpu_recvbuf, count, datatype, rank, tag, recvbuf, count, datatype, rank, tag, global_comm, MPI_STATUS_IGNORE);
    
    free((void*)cpu_sendbuf);
    free((void*)cpu_recvbuf);

    return MPI_SUCCESS;
}

int numa_aware_allreduce(const void* sendbuf,
                               void* recvbuf,
                               int count,
                               MPI_Datatype datatype,
                               MPI_Op op,
                               MPI_Comm comm)
{
   
   int found = -1;
   int i = -1;
   while (i + 1 < NUM_MPIL_COMMS)
   {
      i++;
      MPI_Comm i_comm = comms[i];
      if (i_comm == MPI_COMM_NULL) break;
      if (comm == MPI_COMM_WORLD && i_comm == MPI_COMM_WORLD)
      {
         found = i;
         break;
      }
      int res = 0;
      MPI_Comm_compare(comm, i_comm, &res);
      if (res == MPI_IDENT)
      {
         found = i;
         break;
      }
   }
   
   MPI_Comm leader_group_comm;
   MPI_Comm leader_comm;
   int num_procs;
   int ppn;
   int num_nodes;
   
   if (found >= 0)
   {
      leader_group_comm = leader_group_comms[found];
      leader_comm = leader_comms[found];
      num_procs = num_procss[found];
      ppn = ppns[found];
      num_nodes = num_nodess[found];
   }
   else
   {
      // skip alternative comms for now, only use NUMA-aware on MPI_COMM_WORLD setup in hypre_MPI_Init
      return PMPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
      /*
      while (found + 1 < NUM_MPIL_COMMS)
      {
         found++;
         if (comms[found] == MPI_COMM_NULL) break;
      }
      if (comms[found] != MPI_COMM_NULL)
      {
         comms[found] = MPI_COMM_NULL;
         if (leader_group_comms[found] != MPI_COMM_NULL) MPI_Comm_free(&(leader_group_comms[found]));
         leader_group_comms[found] = MPI_COMM_NULL;
         if (leader_comms[found] != MPI_COMM_NULL) MPI_Comm_free(&(leader_comms[found]));
         leader_comms[found] = MPI_COMM_NULL;
      }
      
      comms[found] = comm;
      
      int rank;
      MPI_Comm_rank(comm, &rank);
      MPI_Comm_size(comm, &num_procs);
      num_procss[found] = num_procs;
      
      // Split global comm into local (per node) communicators
      MPI_Comm local_comm;
      MPI_Comm_split_type(comm,
                           MPI_COMM_TYPE_SHARED,
                           rank,
                           MPI_INFO_NULL,
                           &local_comm);

      int local_rank;
      MPI_Comm_rank(local_comm, &local_rank);
      MPI_Comm_size(local_comm, &ppn);
      ppns[found] = ppn;

      // Split global comm into group (per local rank) communicators
      MPI_Comm group_comm;
      MPI_Comm_split(comm, local_rank, rank, &group_comm);

      int node;
      MPI_Comm_rank(group_comm, &node);

      // Gather arrays for get_node, get_local, and get_global methods
      // These arrays allow for these methods to work with any ordering
      // No longer relying on SMP ordering of processes to nodes!
      // Does rely on constant ppn
      int *global_rank_to_local = (int*)malloc(num_procs * sizeof(int));
      int *global_rank_to_node  = (int*)malloc(num_procs * sizeof(int));
      MPI_Allgather(&local_rank,
                     1,
                     MPI_INT,
                     global_rank_to_local,
                     1,
                     MPI_INT,
                     comm);
      MPI_Allgather(
         &node, 1, MPI_INT, global_rank_to_node, 1, MPI_INT, comm);

      int *ordered_global_ranks = (int*)malloc(num_procs * sizeof(int));
      for (int i = 0; i < num_procs; i++)
      {
         int local                                       = global_rank_to_local[i];
         int node                                        = global_rank_to_node[i];
         ordered_global_ranks[node * ppn + local] = i;
      }

      // Set xcomm variables
      num_nodes = ((num_procs - 1) / ppn) + 1;
      num_nodess[found] = num_nodes;
      int rank_node = global_rank_to_node[rank];

      // Convert to leader_comm (4 leaders per node)
      int num_leaders = 4;
      int procs_per_leader = ppn / num_leaders;
      int leader = local_rank / procs_per_leader;
      int leader_rank = local_rank % procs_per_leader;

      MPI_Comm_split(
         local_comm, local_rank / procs_per_leader, rank, &leader_comm);
         
      leader_comms[found] = leader_comm;

      MPI_Comm_split(comm, leader_rank, rank, &leader_group_comm);
      
      leader_group_comms[found] = leader_group_comm;
      
      free((void *)ordered_global_ranks);
      free((void *)global_rank_to_local);
      free((void *)global_rank_to_node);
      MPI_Comm_free(&group_comm);
      MPI_Comm_free(&local_comm);
      */
   }
   
   if (num_nodes * ppn != num_procs)
   {
      return PMPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
   }
   else
   {
      return allreduce_dissemination_loc_core(
                     sendbuf, recvbuf, count, datatype, op, 
                     comm, leader_group_comm, 
                     leader_comm, 77);
   }
}

int MPI_Allreduce(const void* sendbuf,
                        void* recvbuf,
                        int count,
                        MPI_Datatype datatype,
                        MPI_Op op,
                        MPI_Comm comm)
{
    if (count < 100)
    {
        return numa_aware_allreduce(sendbuf, recvbuf, count, datatype, op, comm);
    }
    else // Only use numa aware for small allreduces
    {
        return PMPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
    }

    return MPI_SUCCESS;
}

HYPRE_Int
hypre_MPI_Allreduce( void              *sendbuf,
                     void              *recvbuf,
                     HYPRE_Int          count,
                     hypre_MPI_Datatype datatype,
                     hypre_MPI_Op       op,
                     hypre_MPI_Comm     comm )
{
   hypre_GpuProfilingPushRange("MPI_Allreduce");

   HYPRE_Int result = MPI_Allreduce(sendbuf, recvbuf, (hypre_int)count,
                                    datatype, op, comm);

   hypre_GpuProfilingPopRange();

   return result;
}

HYPRE_Int
hypre_MPI_Reduce( void               *sendbuf,
                  void               *recvbuf,
                  HYPRE_Int           count,
                  hypre_MPI_Datatype  datatype,
                  hypre_MPI_Op        op,
                  HYPRE_Int           root,
                  hypre_MPI_Comm      comm )
{
   return (HYPRE_Int) MPI_Reduce(sendbuf, recvbuf, (hypre_int)count,
                                 datatype, op, (hypre_int)root, comm);
}

HYPRE_Int
hypre_MPI_Scan( void               *sendbuf,
                void               *recvbuf,
                HYPRE_Int           count,
                hypre_MPI_Datatype  datatype,
                hypre_MPI_Op        op,
                hypre_MPI_Comm      comm )
{
   return (HYPRE_Int) MPI_Scan(sendbuf, recvbuf, (hypre_int)count,
                               datatype, op, comm);
}

HYPRE_Int
hypre_MPI_Request_free( hypre_MPI_Request *request )
{
   return (HYPRE_Int) MPI_Request_free(request);
}

HYPRE_Int
hypre_MPI_Type_contiguous( HYPRE_Int           count,
                           hypre_MPI_Datatype  oldtype,
                           hypre_MPI_Datatype *newtype )
{
   return (HYPRE_Int) MPI_Type_contiguous((hypre_int)count, oldtype, newtype);
}

HYPRE_Int
hypre_MPI_Type_vector( HYPRE_Int           count,
                       HYPRE_Int           blocklength,
                       HYPRE_Int           stride,
                       hypre_MPI_Datatype  oldtype,
                       hypre_MPI_Datatype *newtype )
{
   return (HYPRE_Int) MPI_Type_vector((hypre_int)count, (hypre_int)blocklength,
                                      (hypre_int)stride, oldtype, newtype);
}

HYPRE_Int
hypre_MPI_Type_hvector( HYPRE_Int           count,
                        HYPRE_Int           blocklength,
                        hypre_MPI_Aint      stride,
                        hypre_MPI_Datatype  oldtype,
                        hypre_MPI_Datatype *newtype )
{
#if MPI_VERSION > 1
   return (HYPRE_Int) MPI_Type_create_hvector((hypre_int)count, (hypre_int)blocklength,
                                              stride, oldtype, newtype);
#else
   return (HYPRE_Int) MPI_Type_hvector((hypre_int)count, (hypre_int)blocklength,
                                       stride, oldtype, newtype);
#endif
}

HYPRE_Int
hypre_MPI_Type_struct( HYPRE_Int           count,
                       HYPRE_Int          *array_of_blocklengths,
                       hypre_MPI_Aint     *array_of_displacements,
                       hypre_MPI_Datatype *array_of_types,
                       hypre_MPI_Datatype *newtype )
{
   hypre_int *mpi_array_of_blocklengths;
   HYPRE_Int  i;
   HYPRE_Int  ierr;

   mpi_array_of_blocklengths = hypre_TAlloc(hypre_int,  count, HYPRE_MEMORY_HOST);
   for (i = 0; i < count; i++)
   {
      mpi_array_of_blocklengths[i] = (hypre_int) array_of_blocklengths[i];
   }

#if MPI_VERSION > 1
   ierr = (HYPRE_Int) MPI_Type_create_struct((hypre_int)count, mpi_array_of_blocklengths,
                                             array_of_displacements, array_of_types,
                                             newtype);
#else
   ierr = (HYPRE_Int) MPI_Type_struct((hypre_int)count, mpi_array_of_blocklengths,
                                      array_of_displacements, array_of_types,
                                      newtype);
#endif

   hypre_TFree(mpi_array_of_blocklengths, HYPRE_MEMORY_HOST);

   return ierr;
}

HYPRE_Int
hypre_MPI_Type_commit( hypre_MPI_Datatype *datatype )
{
   return (HYPRE_Int) MPI_Type_commit(datatype);
}

HYPRE_Int
hypre_MPI_Type_free( hypre_MPI_Datatype *datatype )
{
   return (HYPRE_Int) MPI_Type_free(datatype);
}

HYPRE_Int
hypre_MPI_Op_free( hypre_MPI_Op *op )
{
   return (HYPRE_Int) MPI_Op_free(op);
}

HYPRE_Int
hypre_MPI_Op_create( hypre_MPI_User_function *function, hypre_int commute, hypre_MPI_Op *op )
{
   return (HYPRE_Int) MPI_Op_create(function, commute, op);
}

#if defined(HYPRE_USING_GPU) || defined(HYPRE_USING_DEVICE_OPENMP)
HYPRE_Int
hypre_MPI_Comm_split_type( hypre_MPI_Comm comm, HYPRE_Int split_type, HYPRE_Int key,
                           hypre_MPI_Info info, hypre_MPI_Comm *newcomm )
{
   return (HYPRE_Int) MPI_Comm_split_type(comm, split_type, key, info, newcomm );
}

HYPRE_Int
hypre_MPI_Info_create( hypre_MPI_Info *info )
{
   return (HYPRE_Int) MPI_Info_create(info);
}

HYPRE_Int
hypre_MPI_Info_free( hypre_MPI_Info *info )
{
   return (HYPRE_Int) MPI_Info_free(info);
}
#endif

#endif
